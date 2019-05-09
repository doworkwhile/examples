Rails.application.routes.draw do
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
  root to: 'index#index'
  resources :todo_lists, only: [:create, :update, :destroy]
end
