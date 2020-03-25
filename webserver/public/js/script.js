const serverAddress = 'ws://127.0.0.1/';
var socket;
var screens = new Map();

function log(msg) {
    document.getElementById('debug-output').innerHTML = msg;
    console.log(msg);
}

// Set up everything the front-end application needs.
// Called on load for <body>. 
function initialize() {
  socket = new WebSocket(serverAddress);
  socket.onopen = function(event) {
    log('Connection is opened');
  };

  socket.onerror = function (err) {
    log(`Error: ${err}`);
  }

  socket.onclose = function() {
    log('Connection is closed');
  }

  socket.onmessage = function() {
    log(event.data);
  }

  // Push all screens into a map of [screen ID, screen]
  document.querySelectorAll('.screen').forEach(screen => {
    screens.set(screen.id, screen)
  });

  // Set up event listeners
  var connectButton = document.querySelector('#connect');
  connectButton.addEventListener('click', () => setCurrentScreen('waitingScreen'))
}

// Set the currently visible screen to the matching screenID argument.
// If no screen exists matching that argument, do nothing.
function setCurrentScreen(screenID) {
  if (screens.has(screenID)) {
    screens.forEach(screen => {
      if (screen.id === screenID) {
        screen.style.display = 'flex';
      }
      else {
        screen.style.display = 'none';
      }
    });
  }
}

// Enable the connect button if and only if the user has entered something
// into the input form.
function handleTextInputChange() {
  var connectButton = document.querySelector('#connect');
  var inputTextForm = document.querySelector('#lname');
  
  if (inputTextForm.value === '') {
    connectButton.disabled = true;
    connectButton.classList.add('disabled');
  } else {
    connectButton.disabled = false;
    connectButton.classList.remove('disabled');
  }
}

//Testing purposes to change transform matrix
function message() {
  if (socket)
    socket.send("transform");
}
