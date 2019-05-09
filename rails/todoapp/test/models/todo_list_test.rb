require 'test_helper'

class TodoListTest < ActiveSupport::TestCase

  test "should have TodoList Model" do
    TodoList.new
    assert true
  end

  test "TodoList should require a name" do
    t = TodoList.new
    assert_not t.valid?

    todo_list_name = 'test'
    t = TodoList.new(name: todo_list_name)
    assert t.name == todo_list_name
    t.validate
    assert t.errors[:name].empty?
  end

  test "TodoList should have many Todos" do
    t = TodoList.new(name: 'a')
    assert t.todos
  end

end