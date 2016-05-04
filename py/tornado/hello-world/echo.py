import tornado.ioloop
import tornado.web

class EchoHandler(tornado.web.RequestHandler):

    def get(self):
        self._echo()

    def post(self):
        self._echo()

    def delete(self):
        self._echo()

    def _echo(self):
        blob = tornado.escape.json_decode(self.request.body)
        self.write(json.dumps(blob, indent=2))


def make_app():
    return tornado.web.Application([
        (r".*", EchoHandler),
    ])

if __name__ == "__main__":
    app = make_app()
    app.listen(8888)
    tornado.ioloop.IOLoop.current().start()
