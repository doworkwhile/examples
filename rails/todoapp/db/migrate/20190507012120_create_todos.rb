class CreateTodos < ActiveRecord::Migration[5.1]
  def change
    create_table :todos do |t|
      t.string :name, null: false
      t.references :todo_list, foreign_key: true
      t.timestamps
    end
  end
end
