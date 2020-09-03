// "use strict";

// var http = require("http"),
//     url  = require("url"),
//     server;

// server = http.createServer(function (request, response) {
//   request.on("end", function() {
//     var urlObj;

//     switch (request.method) {
//       case "POST":
//         urlObj = url.parse(request.url, true);

//         switch (urlObj.pathname) {
//           case "/api/":
//             console.log(urlObj.query.val);
//             response.end();
//             break;
//         }
//         break;
//     }
//   }).resume();
// }).listen(3200);

var express = require('express');
const bodyParser = require('body-parser');
var http = require("http"),
    url  = require("url"),
    server;

var app = express();
app.use(express.json());
const port = process.env.PORT || 3200;
app.listen(port, () => console.log(`Listening on port ${port}...`));

app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());

// app.get('/', (req, res) => {
//   res.setHeader('Content-Type', 'text/plain');
//   res.json("Hello");
//   //res.sendStatus(200);
// });

app.post('/api', (req, res) => {
  //resではなく送られてきているのでreqをつかうと,送られてくるvalのデータが取れる
  console.log(req.query.val);
  res.setHeader('Content-Type', 'text/plain');
  res.json("Hello");
  //res.sendStatus(200);
});



