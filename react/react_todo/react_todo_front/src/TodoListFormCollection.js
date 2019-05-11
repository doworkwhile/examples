import React from 'react';
import TodoListForm from './TodoListForm.js'

class TodoListFormCollection extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      loaded: false,

      lists: []
    }
    this.loadSuccess = this.loadSuccess.bind(this);
    this.handleNewList = this.handleNewList.bind(this);
    this.handleListDeleted = this.handleListDeleted.bind(this);
  }

  componentWillMount() {
    fetch('lists.json')
      .then(function(res) {
        return res.json();
      })
      .then(this.loadSuccess)
      .catch(() => console.err('Failed to load collection of TodoLists'))
  }

  loadSuccess(response) {
    this.setState({
      loaded: true,

      lists: response
    })
  }

  handleNewList(e) {
    this.setState({

      lists: [...this.state.lists, {}]
    })
  }

  handleListDeleted(index) {
    const splicedLists = this.state.lists;
    splicedLists.splice(index, 1);
    this.setState({
      lists: splicedLists
    })
  }

  render() {
    if (!this.state.loaded) {
      return (<div />)
    }

    return (
      <div>
        <div>
          <button type="button" onClick={this.handleNewList}>New List!</button>
        </div>
        {
          this.state.lists.map( (list,i) => {
            return (
              <TodoListForm key={list.id} index={i} list={list} deleteCallback={this.handleListDeleted} />
            );
          })
        }
      </div>
    );
  }
}

export default TodoListFormCollection;