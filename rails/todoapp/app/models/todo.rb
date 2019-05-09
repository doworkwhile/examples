class Todo < ApplicationRecord

  belongs_to :todo_list, inverse_of: :todos

  validates_presence_of :name
end