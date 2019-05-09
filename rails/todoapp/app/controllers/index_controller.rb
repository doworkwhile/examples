class IndexController < ApplicationController

  def index
    @new_todo_list = TodoList.new
    @new_todo_list.todos.build
    @todo_lists = TodoList.all
    @todo_lists.each { |tl| tl.todos.build }
  end

end