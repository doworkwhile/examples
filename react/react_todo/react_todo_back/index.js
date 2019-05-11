const express = require('express')
const bodyParser = require('body-parser');
const path = require("path");
const app = express();
const port = process.env.PORT || 3001;

app.use(express.static(path.join(__dirname, 'build')));

app.get('/', function(req, res) {
  res.sendFile(path.join(__dirname, 'build', 'index.html'));
});


app.use(bodyParser.json());

const ListsController = require('./lists.js');
app.get('/lists.json', ListsController.index);
app.post('/lists.json', ListsController.create);
app.get('/lists/:id.json', ListsController.show);
app.post('/lists/:id.json', ListsController.update);

app.listen(port, () => console.log(`Example app listening on port ${port}!`))