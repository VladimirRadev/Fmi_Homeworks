const form = document.getElementById('form_id');

let subject_picked = {
    name: "",
    credits: 0,
    type: ""
};
form.addEventListener('submit',(event)=> {
    event.preventDefault();
    const name = document.getElementById('subject_name').value;
    const credits= document.getElementById('credits_count').value;
    const type = document.getElementById('subject_type').value;

    subject_picked= {
        name:name,
        credits:credits,
        type:type,
    };
    fetch('./js2-form-handler.php', {
        method: 'POST',
        headers: {
            'Content-Type':'application/json',
        },
        body: JSON.stringify(subject_picked),
    }).then((response) => {
            return response.json();
        }).then((data) => {
            console.log(data);
        });
});
