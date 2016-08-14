const http = require('http');
const webdriver = require('selenium-webdriver')

const hostname = '127.0.0.1';
const port = 3000;

const standalone_hostname = '127.0.0.1';
const standalone_port = 4444;

const proxy_session = function(req, res) {
    const path = req.url
    const destination = standalone_hostname + ':' + standalone_port + path;
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
        host: standalone_hostname,
        path: path,
        port: standalone_port,
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

const server = http.createServer((req, res) => {
    console.info('BEGIN ' + req.method + ' ' + req.url);
    proxy_session(req, res);

});

server.listen(port, hostname, () => {
  console.info(`Server running at http://${hostname}:${port}/`);
});
