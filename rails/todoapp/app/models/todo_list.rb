class TodoList < ApplicationRecord

  has_many :todos, inverse_of: :todo_list
  accepts_nested_attributes_for :todos, reject_if: :all_blank, allow_destroy: true

  validates_presence_of :name
  validates_presence_of :todos
end