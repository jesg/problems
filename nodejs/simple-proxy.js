const http = require('http');

const hostname = '127.0.0.1';
const port = 3000;

error_handler = function(req, res, msg) {
	res.end();
	console.warn('WARNING ' + msg);
	console.info('END ' + req.method + ' ' + res.statusCode + ' ' + req.url);
}
const cached_sessions = {};
const active_sessions = {'1234': {'host': 'localhost', 'port': 8888, 'cap': {}}};

// cleanup on error
const proxy_session = function(req, res, capture) {
	const session_id = capture[1];
	const session_data = active_sessions[session_id];
	if(!session_data) {
		res.statusCode = 403;
		error_handler(req, res, 'unable to find session ' + session_id);
		return;
	}

	const host = session_data['host'];
	const port = session_data['port'];
	const path = req.url;
	const destination = host + ':' + port + path;
	const callback = (response) => {
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

	const options = {
		host: host,
		path: path,
		port: port,
		method: req.method,
		headers: req.headers
	};

	console.info('BEGIN ' + ' forward to ' + destination);
	const proxy_req = http.request(options, callback);

	req.on('data', function(chunk) {
		proxy_req.write(chunk);
	});

	req.on('end', function() {
		proxy_req.end();
	});
}

const new_session = 0;
const quit_session = 0;
const kill_session = 0;
const reuse_session = 0;
const ping = function(req, res, capture) {
	res.statusCode = 200;
	res.write('pong');
	res.end();
	console.info('END ' + req.method + ' ' + res.statusCode + ' ' + req.url);
}

const handlers = [
	[/^\/session$/, new_session],
	[/^\/session\/([0-9a-z\-]+)$/, quit_session],
	[/^\/session\/([0-9a-z\-]+)\/kill$/, kill_session],
	[/^\/session\/([0-9a-z\-]+)\/reuse$/, reuse_session],
	[/^\/session\/([0-9a-z\-]+)\/[a-z]+/, proxy_session],
	[/^\/ping$/, ping],
]

const server = http.createServer((req, res) => {
	const url = req.url;
	console.info('BEGIN ' + req.method + ' ' + url);

	const handlers_len = handlers.length;
	for(var i = 0; i < handlers_len; i++) {
		const match = url.match(handlers[i][0]);
		if(!match) {
			continue;
		}
		handlers[i][1](req, res, match);
		break;
	}
});

server.listen(port, hostname, () => {
  console.info(`Server running at http://${hostname}:${port}/`);
});
