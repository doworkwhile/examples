class TodoListControllerTest < ActionDispatch::IntegrationTest
  test "should create a TodoList" do
    assert TodoList.count == 0
    post todo_lists_path, params: {
      todo_list: {
        name: 'a',
        todos_attributes: [ {name: 'b'} ]
      }
    }
    assert TodoList.count == 1
    assert_redirected_to root_url
  end
  test "should update a TodoList" do
    update_todo = Todo.new(name: 'b')
    destroy_todo = Todo.new(name: 'c')
    t = TodoList.create!(name: 'a', todos: [update_todo, destroy_todo])
    assert TodoList.count == 1
    assert Todo.count == 2

    new_updated_todo_name = 'd'
    put todo_list_path(t), params: {
      todo_list: {
        name: 'c',
        todos_attributes: [
          { id: update_todo.id, name: new_updated_todo_name },
          { id: destroy_todo.id, _destroy: 't' }
        ]
      }
    }

    update_todo.reload
    assert update_todo.name == new_updated_todo_name
    assert t.todos.count == 1
    assert_redirected_to root_url
  end
  test "should destroy a TodoList" do
    todo = Todo.new(name: 'b')
    t = TodoList.create!(name: 'a', todos: [todo])

    put todo_list_path(t), params: {
      commit: 'Destroy'
    }
    assert TodoList.count == 0
    assert_redirected_to root_url
  end
end