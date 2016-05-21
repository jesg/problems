const http = require('http');

const hostname = '127.0.0.1';
const port = 3000;

const proxy = function(req, res, host, path, port) {
	callback = (response) => {
		res.statusCode = response.statusCode;
		res.headers = response.headers;

		response.on('data', function (chunk) {
			res.write(chunk);
		});

		response.on('end', function () {
			res.end();
		});
	}

	var options = {
		host: host,
		path: path,
		port: port,
		method: req.method,
		headers: req.headers
	};

	var proxy_req = http.request(options, callback);

	req.on('data', function(chunk) {
		proxy_req.write(chunk);
	});

	req.on('end', function() {
		proxy_req.end();
	});
}

const server = http.createServer((req, res) => {

	proxy(req, res, 'localhost', '/bla', 8888)

});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});

// echo cats
// curl --data 'cats' http://localhost:3000
