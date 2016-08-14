const http = require('http');
const buffer = require('buffer');
const webdriver = require('selenium-webdriver')

const hostname = '127.0.0.1';
const port = 3000;

const error_handler = function(req, res, msg) {
    res.write(msg);
    res.end();
    console.warn('WARNING ' + msg);
    console.info('END ' + req.method + ' ' + res.statusCode + ' ' + req.url);
}

const chrome_factory = function(driver) {
    // const cap = webdriver.
}
const cached_sessions = {};
const active_sessions = {'1234': {'host': 'localhost', 'port': 8888, 'cap': {}}};
const new_session = function(req, res, match) {
    if(req.method != 'POST') {
        res.statusCode = 404;
        error_handler(req, res, 'must use http POST when creating a new session');
        return;
    }

    var chunks = '';
    req.on('data', function(chunk) {
        chunks += chunk;
    });

    req.on('end', function() {
        try {
            var body = JSON.parse(chunks);
            console.info(body);

            const cap = webdriver.Capabilities.phantomjs();
            cap.set('phantomjs.cli.args', ['--ignore-ssl-errors=true', '--webdriver=9000']);
            const builder = new webdriver.Builder()
            .withCapabilities(cap);
            // .forBrowser('chrome')
            console.log(builder);

            const driver = builder.build()

driver.getCapabilities()
            .then(function(capabilities) {
                const plain_caps = {};
                capabilities.forEach(function(v, k) {
                    plain_caps[k] = v;
                });
                driver.getSession()
                .then(function(session_id) {
                    // also need host and port
                    const host = 'localhost';
                    // look in http executors ... need to find port
                    // the port is hidden and not reachable after the browser is created
                    console.info('NEW SESSION ' + session_id.getId() + "\n" + JSON.stringify(plain_caps, null, 2));
                    res.write(JSON.stringify({
                        'sessionId': session_id.getId(),
                        'status': 0,
                        'value': plain_caps
                    }));
                    res.end();
                    // driver.quit();
                    console.info('END ' + req.method +' ' + res.statusCode + ' ' + req.url);
                });
            })
        } catch(err) {
            console.warn(err);
            error_handler(req, res, 'unable to create browser');
            return;
        }
    });
}

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
