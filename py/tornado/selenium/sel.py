# -*- coding: utf-8 -*-

#Copyright © 2016 <Jason Gowan>
#
#Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
#
#The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
#
#THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

import tornado.web
import tornado.gen
import tornado.httpclient
import tornado.escape
from selenium import webdriver as wd
import signal
import sys


class SessionCache(object):

    def __init__(self):
        self.active_sessions = {}
        self.cached_sessions = []

    def add_session(self, session_id, endpoint, capabilities, process):
        self.active_sessions[session_id] = dict(
            session_id=session_id,
            endpoint=endpoint,
            capabilities=capabilities,
            process=process,
        )

    def get_endpoint(self, session_id):
        return self.active_sessions[session_id]['endpoint']

    def get_process(self, session_id):
        return self.active_sessions[session_id]['process']

    def count(self):
        return len(self.cached_sessions)

    def recycle(self, session_id):
        tmp = self.active_sessions[session_id]
        self.cached_sessions.append(tmp.copy())
        del self.active_sessions[session_id]

    def remove(self, session_id):
        del self.active_sessions[session_id]

    def pop(self):
        tmp = self.cached_sessions.pop()
        self.active_sessions[tmp['session_id']] = tmp
        return tmp


class BaseHandler(tornado.web.RequestHandler):


    # default timeout is 5min
    CONNECT_TIMEOUT = 300.0
    REQUEST_TIMEOUT = 300.0

    def initialize(self, session_cache):
        self.session_cache = session_cache


class ProxySessionHandler(BaseHandler):

    @tornado.gen.coroutine
    def get(self, session_id):
        uri = self.request.uri
        endpoint = self.session_cache.get_endpoint(session_id)
        http = tornado.httpclient.AsyncHTTPClient()
        response = yield http.fetch(
            tornado.httpclient.HTTPRequest(
                url='{0}{1}'.format(endpoint, uri),
                headers=self.request.headers,
                connect_timeout=self.CONNECT_TIMEOUT,
                request_timeout=self.REQUEST_TIMEOUT,
            )
        )
        self.set_status(response.code)
        for k, v in response.headers.get_all():
            self.add_header(k, v)
        self.write(response.body)


    @tornado.gen.coroutine
    def post(self, session_id):
        uri = self.request.uri
        endpoint = self.session_cache.get_endpoint(session_id)
        http = tornado.httpclient.AsyncHTTPClient()
        response = yield http.fetch(
            tornado.httpclient.HTTPRequest(
                url='{0}{1}'.format(endpoint, uri),
                headers=self.request.headers,
                body=self.request.body,
                method='POST',
                connect_timeout=self.CONNECT_TIMEOUT,
                request_timeout=self.REQUEST_TIMEOUT,
            )
        )
        self.set_status(response.code)
        for k, v in response.headers.get_all():
            self.add_header(k, v)
        self.write(response.body)


class DeleteSessionHandler(BaseHandler):

    def delete(self, session_id):
        endpoint = self.session_cache.get_endpoint(session_id)
        process = self.session_cache.get_process(session_id)
        self.session_cache.remove(session_id)
        uri = self.request.uri
        http = tornado.httpclient.HTTPClient()
        response = http.fetch(
            tornado.httpclient.HTTPRequest(
                '{0}{1}'.format(endpoint, uri),
                headers=self.request.headers,
                method=self.request.method,
            )
        )
        http.close()
        self.set_status(response.code)
        for k, v in response.headers.get_all():
            self.add_header(k, v)
        self.write(response.body)


class KillSessionHandler(BaseHandler):

    def delete(self, session_id):
        endpoint = self.session_cache.get_endpoint(session_id)
        process = self.session_cache.get_process(session_id)
        self.session_cache.remove(session_id)
        uri = self.request.uri
        http = tornado.httpclient.HTTPClient()
        response = http.fetch(
            tornado.httpclient.HTTPRequest(
                '{0}{1}'.format(endpoint, uri),
                headers=self.request.headers,
                method=self.request.method,
            )
        )
        http.close()
        process.send_signal(signal.SIGTERM)
        self.set_status(response.code)
        for k, v in response.headers.get_all():
            self.add_header(k, v)
        self.write(response.body)


class RecycleSessionHandler(BaseHandler):

    def post(self, session_id):
        self.session_cache.recycle(session_id)
        self.set_status(200)
        self.write(dict(
            sessionId=session_id,
            status=0,
            value=dict(),
        ))


class NewSessionHandler(BaseHandler):

    def post(self):
        session_id = None
        capabilities = None
        body = tornado.escape.json_decode(self.request.body)

        if self.session_cache.count() == 0:
            driver = wd.PhantomJS(desired_capabilities=body['desiredCapabilities'])
            driver.get('about:blank')
            endpoint = driver.service.service_url
            session_id = driver.session_id
            print('New Session {0}, endpoint {1}'.format(session_id, endpoint), file=sys.stderr)
            capabilities = driver.capabilities
            process = driver.service.process
            self.session_cache.add_session(session_id, endpoint, capabilities, process)
        else:
            blob = self.session_cache.pop()
            session_id = blob['session_id']
            capabilities = blob['capabilities']
            print('Reuse Session {0}, endpoint {1}'.format(session_id, blob['endpoint']), file=sys.stderr)

        self.write(dict(
            sessionId=session_id,
            status=0,
            value=capabilities,
        ))


class PingHandler(tornado.web.RequestHandler):

    @tornado.gen.coroutine
    def get(self):
        self.write(u'pong')

def simple_logger(handler):
    print('{0} {1}'.format(handler.request.method, handler.request.uri), file=sys.stderr)

def make_app():
    session_cache = SessionCache()
    return tornado.web.Application([
        (r"/ping", PingHandler),
        (r"/session", NewSessionHandler, dict(session_cache=session_cache)),
        (r"/session/([0-9-a-z]+)", DeleteSessionHandler, dict(session_cache=session_cache)),
        (r"/session/([0-9-a-z]+)/kill", KillSessionHandler, dict(session_cache=session_cache)),
        (r"/session/([0-9-a-z]+)/recycle", RecycleSessionHandler, dict(session_cache=session_cache)),
        (r"/session/([0-9-a-z]+)/[a-z]+.*", ProxySessionHandler, dict(session_cache=session_cache)),
    ], log_function=simple_logger)

if __name__ == "__main__":
    app = make_app()
    app.listen(8889)
    tornado.ioloop.IOLoop.current().start()
