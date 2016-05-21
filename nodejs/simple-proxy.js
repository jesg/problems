const http = require('http');

const hostname = '127.0.0.1';
const port = 3000;

const proxy = function(req, res, host, path, port) {
	const destination = host + ':' + port + path;
	console.info('BEGIN ' + ' forward to ' + destination);
	callback = (response) => {
		res.statusCode = response.statusCode;
		console.info('END ' + ' forward to ' + response.statusCode + ' ' + destination);
		res.headers = response.headers;

		response.on('data', function (chunk) {
			res.write(chunk);
		});

		response.on('end', function () {
			res.end();
			console.info('END ' + req.method + ' ' + res.statusCode + ' ' + path);
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
	console.info('BEGIN ' + req.method + ' ' + req.url);

	proxy(req, res, 'localhost', req.url, 8888)

});

server.listen(port, hostname, () => {
  console.info(`Server running at http://${hostname}:${port}/`);
});

// echo cats
// curl --data 'cats' http://localhost:3000
