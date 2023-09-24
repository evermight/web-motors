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
document.addEventListener('DOMContentLoaded', _ => {
  document.querySelectorAll('[name=action]').forEach(btn => {
    btn.addEventListener('click', evt => 
      fetch('./process.php?action='+evt.currentTarget.value)
      .then(res => res.text())
      .then(res => {
        document.getElementById('current-action').innerHTML = DISPLAY[res].label;
        document.getElementById('current-action').className = DISPLAY[res].cls;
      })
    );
  });
});
