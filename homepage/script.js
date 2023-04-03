const input = document.querySelector('#exampleFormControlInput1');
const btn = document.querySelector('#btn');
const ul = document.querySelector('#ul');
let li;

btn.addEventListener('click', () => {
  li = document.createElement('li');
  li.innerHTML = input.value;
  ul.appendChild(li);
})
