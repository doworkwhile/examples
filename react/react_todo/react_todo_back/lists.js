const Ajv = require('ajv');
const schema = Ajv({ coerceTypes: true, removeAdditional: "all" });
const listSchema = schema.compile({
  properties: {
    id: { type: 'integer' },
    name: { type: 'string' },

    todos: {
      type: 'array',
      minItems: 1,
      maxItems: 10,

      items: {
        type: "object",
        properties: {
          id: { type: 'integer' },
          name: { type: 'string'}
        },
        required: ["name"]
      }
    },
  },
  required: ["name", "todos"]
});

var lastListId = 2;
var lastTodoId = 6;
var listData1 = {
  id: 1,
  name: 'List 1',
  todos: [
    { id: 1, name: 'Item 1.1' },
    { id: 2, name: 'Item 1.2' },
    { id: 3, name: 'Item 1.3' }
  ]
};
var listData2 = {
  id: 2,
  name: 'List 2',
  todos: [
    { id: 4, name: 'Item 2.1' },
    { id: 5, name: 'Item 2.2' },
    { id: 6, name: 'Item 2.3' }
  ]
};
var lists = [ listData1, listData2 ];

function listIndex(req, res) {
  res.json(lists);
}

function listShow(req, res) {
  let id = req.params.id;
  let realID = id - 1;
  let validID = realID >= 0 && realID < lists.length;

  if (!validID) {
    res.status(404);
    res.json({});
    return;
  }

  res.json(lists[realID]);
}

function listUpdate(req, res) {
  let id = req.params.id;
  let realID;
  for (let i = 0; i < lists.length; i++) {
    if (lists[i].id == id) {
      realID = i;
      break;
    }
  }
  let validID = realID >= 0 && realID < lists.length;

  if (!validID) {
    res.status(404);
    res.json({});
    return;
  }

  if (req.body.destroy == true) {
    doDestroy(realID, req, res);
  } else {
    doUpdate(lists[realID], req, res);
  }
}

function doUpdate(withList, req, res) {
  var valid = listSchema(req.body);
  if (!valid) {
    res.status(400);
    res.json(withList);
    return;
  }

  Object.assign(withList, req.body);
  // set new ids on todos
  for (var i = 0; i < withList.todos.length; i++) {
    var todo = withList.todos[i];
    if (todo.id === undefined) {
      todo.id = ++lastTodoId;
    }
  }
  res.json(withList);
}

function doDestroy(listID, res, res) {
  lists.splice(listID, 1);
  res.json({});
}

function listCreate(req, res) {
  var valid = listSchema(req.body);

  if (!valid || lists.length > 10) {
    res.status(400);
    res.json({});
    return;
  }

  req.body.id = ++lastListId;
  for (var i = 0; i < req.body.todos.length; i++) {
    req.body.todos[i].id = ++lastTodoId;
  }

  lists.push(req.body)
  res.json(req.body);
}

module.exports = {
  index: listIndex,
  create: listCreate,
  show: listShow,
  update: listUpdate
};