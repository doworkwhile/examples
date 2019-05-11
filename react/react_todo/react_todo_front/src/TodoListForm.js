import React from 'react';

class TodoListForm extends React.Component {
  constructor(props) {
    super(props);
    var withList = props.list || {};
    this.state = {
      setName: withList.name || null,
      id: withList.id || null,
      name: withList.name || null,
      todos: withList.todos || [{}]
    };
    this.handleSubmit = this.handleSubmit.bind(this);
    this.handleListNameChange = this.handleListNameChange.bind(this);
    this.handleTodoNameChange = this.handleTodoNameChange.bind(this);
    this.handleTodoAddRMClick = this.handleTodoAddRMClick.bind(this);
    this.loadSuccess = this.loadSuccess.bind(this);
    this.loadFail = this.loadFail.bind(this);
    this.doDelete = this.doDelete.bind(this);
  }

  loadSuccess(response) {
    this.setState({
      id: response.id,
      name: response.name,
      todos: response.todos,
      setName: response.name,
    })
  }

  loadFail() {
    alert('Failed to Create or Save!')
  }

  handleSubmit(e) {
    if (this.state.id) {
      this.doUpdate();
    } else {
      this.doCreate();
    }
    e.preventDefault();
  }

  doUpdate() {
    fetch('lists/' + this.state.id + '.json', {
        method: 'post',
        body: JSON.stringify(this.state),
        headers: {
          'Content-Type': 'application/json'
        }
      })
      .then(function(response) {
        if (response.ok) {
          return response.json();
        } else {
          throw new Error();
        }
      })
      .then(this.loadSuccess)
      .catch(this.loadFail)
  }

  doCreate() {
    fetch('lists.json', {
        method: 'post',
        body: JSON.stringify(this.state),
        headers: {
          'Content-Type': 'application/json'
        }
      })
      .then(function(response) {
        if (response.ok) {
          return response.json();
        } else {
          throw new Error();
        }
      })
      .then(this.loadSuccess)
      .catch(this.loadFail)
  }

  doDelete() {
    fetch('lists/' + this.state.id + '.json', {
        method: 'post',
        body: JSON.stringify({
          destroy: true
        }),
        headers: {
          'Content-Type': 'application/json'
        }
      })
      .then(function(response) {
        if (response.ok) {
          return response.json();
        } else {
          throw new Error();
        }
      })
      .then(() => {
        this.props.deleteCallback(this.props.index)
      })
      .catch(this.loadFail)
  }

  handleListNameChange(e) {
    this.setState({ name: e.target.value });
  }

  handleTodoNameChange(i, name) {
    this.setState(state => {
      const todos = state.todos;
      todos[i].name = name;
      return {
        todos: todos
      }
    })
  }

  handleTodoAddRMClick(i) {
    var add = (i+1 === this.state.todos.length);
    this.setState(state => {
      let todos = state.todos;

      if (add) {
        todos.push({})
      } else {
        todos.splice(i, 1);
      }

      return {
        todos: todos
      }
    });
  }



  render() {
    let deleteButton;
    if (this.state.id) {
      deleteButton = <button type="button" onClick={() => this.doDelete()}>DELETE</button>
    }

    return (
      <form onSubmit={this.handleSubmit}>
        <h2>List {this.state.id}: {this.state.setName}</h2>
        <input type="text" onChange={this.handleListNameChange} value={this.state.name || ''} />
        <div>
          {
            this.state.todos.map((todo, i) => {
              return (
                <div key={i}>
                  Todo {i+1}:
                  <input type="text" onChange={(e) => this.handleTodoNameChange(i, e.target.value)} value={todo.name || ''} />
                  <button type="button" onClick={() => this.handleTodoAddRMClick(i)}>
                    {i+1 === this.state.todos.length ? '+' : '-'}
                  </button>
                </div>
              );
            })
          }
          <button type="submit">SAVE</button>
          {deleteButton}
        </div>
      </form>
    );
  }
}

export default TodoListForm;