const http = require('http');

var options = {
  host: 'localhost',
  path: '/bla',
  port: '8888',
  headers: {'custom': 'Custom Header Demo works'}
};

callback = function(response) {
  var str = ''
  response.on('data', function (chunk) {
    str += chunk;
  });

  response.on('end', function () {
    console.log(str);
  });
}

var req = http.request(options, callback);
req.end();
