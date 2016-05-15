const http = require('http');

const hostname = '127.0.0.1';
const port = 3000;

const server = http.createServer((req, res) => {
  res.statusCode = 200;
  res.setHeader('Content-Type', 'text/plain');

	req.on('data', function(chunk) {
		res.write(chunk);
	});

	req.on('end', function() {
		res.end();
	});
});

server.listen(port, hostname, () => {
  console.log(`Server running at http://${hostname}:${port}/`);
});

// echo cats
// curl --data 'cats' http://localhost:3000
