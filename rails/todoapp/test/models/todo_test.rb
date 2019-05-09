require 'test_helper'

class TodoTest < ActiveSupport::TestCase

  test "should have Todo model" do
    Todo.new
    assert true
  end

  test "Todo should require a name" do
    t = Todo.new
    assert_not t.valid?

    todo_name = 'test'
    list = TodoList.new(name: 'a')
    t = Todo.new(name: todo_name, todo_list: list)
    assert t.name == todo_name
    assert t.valid?
  end

  test "Todo should belong_to a TodoList" do
    list = TodoList.new(name: 'a')
    t = Todo.new(todo_list: list)
    assert t.todo_list
  end
end