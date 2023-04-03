# Minimalist and functional To-Do List

#### Video Demo: https://youtu.be/8g2b2ATpxNc

#### Description:
** This is a simple _To-Do List_, but let me explain to you all why you need to use one every day.

## Main idea:

Everyday all of us has tasks to do during the day, and there are a lot of ways to note all of your doings, like a notebook, a board which you can write, or maybe your own mind if you have a good memory. But all of this ways of taking notes of tasks has problems. You can lose a paper, your can lose board's pen or forgot your tasks.

## Why you should use

So let me list couple of problems that you might have if you do not use Apps or Sites of To-Do Lists:
  Using a lot of paper means a lot of trees.
  Your cat or dog can simply eat your notes.
  Boards gets really ugly after couple days of using it, when you erase notes.
  Using your memory can be really bad, it is very easy to forget things during a day of work, and forget tasks is awful.

That is why I came up with a minimalist and simple(but functional) _To-Do List_, so you can open it and leave in your browser, and mark the tasks that you have done, and maybe erase them. Isn't that amazing?

## Technologies I used:
  JavaScript
  HTML
  CSS
  REACT.JS
  React Hooks
  React Router Dom
  NPM

## How the site was made

The website is made of _React.JS_, a _framework_ from _javascript_ to build websites. It has a login page, so you can type your name to display on the main page. After the login, you will be redirected to the main page, where you can type your tasks and hit the button "Confirm", and the task will be saved in the page. You are free to add as much tasks you want, and check them with a checkbox, or erase to free up some space. The name displayed in the main page is saved by localStorage.setItem() function and localStorage.getItem() function, so the browser can save the name you typed in, and put it as a data inside the browser local storage. It is executed via node package manager, which will put the web application into the browser.

## Routing

The website uses React Router Dom for route, in the index.js has the <BrowserRouter> tag, that allows react to use other tags for route, such as <Switch> to switch between routes, and <Route> to indicates which component will be connected with the route.
The login page uses "/" as route, and the main page uses "/todo" as route.

## Improvements I would do

The website is very simple, but there it goes some improvements I would do to make the experience better:
  Insert "todos" data into a database, so the user can reload the page and still sees it
  Insert "todos" into the localStorage as another alternative for database
  Create a database to save users and passwords to log in and uses "todos" data from its ID
  Ability to change user's details and create more details to the user
  Notifications on user's email when register in the website


## More explanation

The thing about this project is that it is very simple, but can help a lot if it is used by people who has a lot of tasks to do everyday.

## Directories

I wrote the project in the src/ directory. It has couple more directories that I wrote my code on. Components/ where I wrote all Components I used. Pages/ where I wrote my whole page code, so I could use components inside it. Styles/ where I wrote css code for my project. The src/ has all of it and other configs for React

It might be simple, but it works!

## How to use the project:
#### git clone on the url
#### 'npm install' on command-line to install dependencies
#### 'npm start' on command-line to start the web application**
#### open localhost:3000 in your browser

