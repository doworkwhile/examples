(window.webpackJsonp=window.webpackJsonp||[]).push([[0],{10:function(e,t,n){e.exports=n(18)},16:function(e,t,n){},17:function(e,t,n){},18:function(e,t,n){"use strict";n.r(t);var a=n(0),o=n.n(a),i=n(8),s=n.n(i),l=(n(16),n(17),n(9)),d=n(2),c=n(3),r=n(5),u=n(4),h=n(1),m=n(6),b=function(e){function t(e){var n;Object(d.a)(this,t),n=Object(r.a)(this,Object(u.a)(t).call(this,e));var a=e.list||{};return n.state={setName:a.name||null,id:a.id||null,name:a.name||null,todos:a.todos||[{}]},n.handleSubmit=n.handleSubmit.bind(Object(h.a)(n)),n.handleListNameChange=n.handleListNameChange.bind(Object(h.a)(n)),n.handleTodoNameChange=n.handleTodoNameChange.bind(Object(h.a)(n)),n.handleTodoAddRMClick=n.handleTodoAddRMClick.bind(Object(h.a)(n)),n.loadSuccess=n.loadSuccess.bind(Object(h.a)(n)),n.loadFail=n.loadFail.bind(Object(h.a)(n)),n.doDelete=n.doDelete.bind(Object(h.a)(n)),n}return Object(m.a)(t,e),Object(c.a)(t,[{key:"loadSuccess",value:function(e){this.setState({id:e.id,name:e.name,todos:e.todos,setName:e.name})}},{key:"loadFail",value:function(){alert("Failed to Create or Save!")}},{key:"handleSubmit",value:function(e){this.state.id?this.doUpdate():this.doCreate(),e.preventDefault()}},{key:"doUpdate",value:function(){fetch("lists/"+this.state.id+".json",{method:"post",body:JSON.stringify(this.state),headers:{"Content-Type":"application/json"}}).then(function(e){if(e.ok)return e.json();throw new Error}).then(this.loadSuccess).catch(this.loadFail)}},{key:"doCreate",value:function(){fetch("lists.json",{method:"post",body:JSON.stringify(this.state),headers:{"Content-Type":"application/json"}}).then(function(e){if(e.ok)return e.json();throw new Error}).then(this.loadSuccess).catch(this.loadFail)}},{key:"doDelete",value:function(){var e=this;fetch("lists/"+this.state.id+".json",{method:"post",body:JSON.stringify({destroy:!0}),headers:{"Content-Type":"application/json"}}).then(function(e){if(e.ok)return e.json();throw new Error}).then(function(){e.props.deleteCallback(e.props.index)}).catch(this.loadFail)}},{key:"handleListNameChange",value:function(e){this.setState({name:e.target.value})}},{key:"handleTodoNameChange",value:function(e,t){this.setState(function(n){var a=n.todos;return a[e].name=t,{todos:a}})}},{key:"handleTodoAddRMClick",value:function(e){var t=e+1===this.state.todos.length;this.setState(function(n){var a=n.todos;return t?a.push({}):a.splice(e,1),{todos:a}})}},{key:"render",value:function(){var e,t=this;return this.state.id&&(e=o.a.createElement("button",{type:"button",onClick:function(){return t.doDelete()}},"DELETE")),o.a.createElement("form",{onSubmit:this.handleSubmit},o.a.createElement("h2",null,"List ",this.state.id,": ",this.state.setName),o.a.createElement("input",{type:"text",onChange:this.handleListNameChange,value:this.state.name||""}),o.a.createElement("div",null,this.state.todos.map(function(e,n){return o.a.createElement("div",{key:n},"Todo ",n+1,":",o.a.createElement("input",{type:"text",onChange:function(e){return t.handleTodoNameChange(n,e.target.value)},value:e.name||""}),o.a.createElement("button",{type:"button",onClick:function(){return t.handleTodoAddRMClick(n)}},n+1===t.state.todos.length?"+":"-"))}),o.a.createElement("button",{type:"submit"},"SAVE"),e))}}]),t}(o.a.Component),f=function(e){function t(e){var n;return Object(d.a)(this,t),(n=Object(r.a)(this,Object(u.a)(t).call(this,e))).state={loaded:!1,lists:[]},n.loadSuccess=n.loadSuccess.bind(Object(h.a)(n)),n.handleNewList=n.handleNewList.bind(Object(h.a)(n)),n.handleListDeleted=n.handleListDeleted.bind(Object(h.a)(n)),n}return Object(m.a)(t,e),Object(c.a)(t,[{key:"componentWillMount",value:function(){fetch("lists.json").then(function(e){return e.json()}).then(this.loadSuccess).catch(function(){return console.err("Failed to load collection of TodoLists")})}},{key:"loadSuccess",value:function(e){this.setState({loaded:!0,lists:e})}},{key:"handleNewList",value:function(e){this.setState({lists:[].concat(Object(l.a)(this.state.lists),[{}])})}},{key:"handleListDeleted",value:function(e){var t=this.state.lists;t.splice(e,1),this.setState({lists:t})}},{key:"render",value:function(){var e=this;return this.state.loaded?o.a.createElement("div",null,o.a.createElement("div",null,o.a.createElement("button",{type:"button",onClick:this.handleNewList},"New List!")),this.state.lists.map(function(t,n){return o.a.createElement(b,{key:t.id,index:n,list:t,deleteCallback:e.handleListDeleted})})):o.a.createElement("div",null)}}]),t}(o.a.Component);var p=function(){return o.a.createElement("div",{className:"App"},o.a.createElement(f,null))};Boolean("localhost"===window.location.hostname||"[::1]"===window.location.hostname||window.location.hostname.match(/^127(?:\.(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)){3}$/));s.a.render(o.a.createElement(p,null),document.getElementById("root")),"serviceWorker"in navigator&&navigator.serviceWorker.ready.then(function(e){e.unregister()})}},[[10,1,2]]]);
//# sourceMappingURL=main.1e9a7623.chunk.js.map