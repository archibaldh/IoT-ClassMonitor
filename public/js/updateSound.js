// public/js/updateSound.js
function updateSoundValue() {
    // Use AJAX to fetch the sound value from the server
    fetch('/api/soundValue')
        .then(response => response.json())
        .then(data => {
            // Update the value in the HTML
            document.getElementById('soundValue').textContent = data.soundValue;
        });
}

setInterval(updateSoundValue, 250);

// Initial call to update the sound value
updateSoundValue();
