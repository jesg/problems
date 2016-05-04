import tornado.ioloop
import tornado.web
import tornado.gen
import tornado.httpclient

class MainHandler(tornado.web.RequestHandler):

    @tornado.gen.coroutine
    def get(self):
        http = tornado.httpclient.AsyncHTTPClient()
        response = yield http.fetch('http://localhost:8888/', headers=self.request.headers)
        self.set_status(response.code)
        for k, v in response.headers.get_all():
            self.add_header(k, v)
        self.write(response.body)

def make_app():
    return tornado.web.Application([
        (r"/", MainHandler),
    ])

if __name__ == "__main__":
    app = make_app()
    app.listen(8889)
    tornado.ioloop.IOLoop.current().start()
