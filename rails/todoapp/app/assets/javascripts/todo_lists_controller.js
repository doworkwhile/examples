var TodoListController = (function () {

  // when a remove button is clicked.
  // (we don't need to check if it's the last one,
  //  because the last button will always be an add)
  function morelessButtonRm($button) {
    $idElem = $button
      .siblings('input[name="todo_list[todos_attributes][][id]"]');
    idVal = $idElem.val();

    $idElem.siblings().remove();

    $destroyElem = $idElem.clone();
    destroyElemNewName = $destroyElem.attr('name').replace('id', '_destroy')
    $destroyElem.attr('name', destroyElemNewName);
    $destroyElem.val('t');

    $idElem.after($destroyElem);
  }

  // when an add button is clicked
  function morelessButtonAdd($button) {
    $parent = $button.parents('.todo--fields');
    $clone = $parent.clone();
    $parent.after($clone);

    $button
      .removeClass('todos--add')
      .addClass('todos--rm')
      .html('-');

    // reset the fields in our cloned todo
    $clone.find('input').val('');

    bindTodoListFormActions();
  }


  // when a button is clicked we need to differentiate an add vs remove
  function morelessButtonClick(e) {
    var $e = $(e.target);
    var isAdd = $e.hasClass('todos--add');
    var isRm = $e.hasClass('todos--rm');

    if (isAdd) {
      morelessButtonAdd($e);
    } else if (isRm) {
      morelessButtonRm($e);
    }
  }

  // find the buttons to add/remove the todos & bind a click event
  function bindTodoListFormActions() {
    var $morelessButtons = $('button.todos--moreless');

    $morelessButtons
      .off('click', morelessButtonClick)
      .on('click', morelessButtonClick);
  }

  return {
    bind: bindTodoListFormActions
  }
})();