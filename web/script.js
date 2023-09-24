const DISPLAY = {
   "ff":{"cls":"", "label":"&uarr;"},
   "fs":{"cls":"", "label":"&larr;"},
   "ss":{"cls":"", "label":"&#9632;"},
   "sf":{"cls":"", "label":"&rarr;"},
   "bb":{"cls":"", "label":"&darr;"},
   "bf":{"cls":"", "label":"&#9100;"},
   "ss":{"cls":"", "label":"&#9632;"},
   "fb":{"cls":"invert", "label":"&#9100;"}
};
const setBtn = val => {
  document.querySelectorAll('[name=action]').forEach(btn=>btn.classList.remove('active'));
  const btn = document.querySelector('[name=action][value='+val+']').classList.add('active');
  if(btn) {
    btn.classList.add('active');
  }

  document.getElementById('current-action').innerHTML = DISPLAY[val].label;
  document.getElementById('current-action').className = DISPLAY[val].cls;
};
document.addEventListener('DOMContentLoaded', _ => {
  if(window.location.search.match(/debug=\d+/)) {
    document.getElementById('current-action').setAttribute('data-visible','1');
  }
  document.querySelectorAll('[name=action]').forEach(btn => {
    // If there are no other buttons pressed, then stop all actions
    btn.addEventListener('focusout', evt => {
      if(document.querySelectorAll('[name="action"]:focus').length < 1) {
        fetch('./process.php?action=ss')
        .then(res => res.text())
        .then(res => setBtn(res));
      }
    });
    btn.addEventListener('click', evt => 
      fetch('./process.php?action='+evt.currentTarget.value)
      .then(res => res.text())
      .then(res => setBtn(res))
    );
  });
});
