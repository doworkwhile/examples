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
end