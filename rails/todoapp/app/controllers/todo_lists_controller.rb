class TodoListsController < ApplicationController

  def create
    redirect_to root_url

    create_params = params.require(:todo_list).permit(:name, todos_attributes: [:name])
    name_param = create_params[:name]
    todo_list = TodoList.create(create_params)

    if todo_list.valid?
      flash[:notice] = "TodoList \"#{name_param}\" was created!"
      return
    end

    if todo_list.name.blank?
      flash[:alert] = 'New TodoList requires a name!'
      return
    end

    if todo_list.todos.size == 0
      flash[:alert] = 'New TodoList requires at least 1 Todo!'
      return
    end

    flash[:alert] = 'New TodoList could not be created!'
  end

  def update
    redirect_to root_url

    if params[:commit] == 'Destroy'
      do_destroy
    else
      do_update
    end
  end

  def do_update
    id_param = params.require(:id)
    todo_list = TodoList.find(id_param)
    update_params = params.require(:todo_list).permit(:name, todos_attributes: [:id, :name, :_destroy])
    updated = todo_list.update_attributes(update_params)

    if updated
      flash[:notice] = "TodoList \"#{todo_list.name}\" was updated!"
      return
    end

    if todo_list.name.blank?
      flash[:alert] = 'TodoList requires a name!'
      return
    end

    if todo_list.todos.size == 0
      flash[:alert] = 'TodoList requires at least 1 Todo!'
      return
    end

    flash[:alert] = 'TodoList could not be updated!'
  end

  def do_destroy
    id_param = params.require(:id)
    todo_list = TodoList.find(id_param)
    destroyed = todo_list.destroy

    unless destroyed
      flash[:alert] = 'TodoList could not be destroyed!'
      return
    end

    flash[:notice] = "TodoList \"#{todo_list.name}\" was destroyed!"
  end

end