const form = document.getElementById('subject_form');
const ul = document.getElementById('records');

let obj = {
    email: "",
    first_name: "",
    last_name: "",
    type: "",
};
form.addEventListener('submit', (event)=> {
    event.preventDefault();
    const email= document.getElementById('email').value;
    const first_name = document.getElementById('first_name').value;
    const last_name = document.getElementById('last_name').value;
    const type = document.getElementById('subject_type').value;
    obj = {
        email: email,
        first_name: first_name,
        last_name: last_name,
        type: type
    };

    fetch('./form-handler.php', {
        method:'POST',
        body: JSON.stringify(obj),
        headers: {
            'Content-Type':'application/json',
        }
    }) 
        .then((response) => {
            return response.json();
        })
        .then((data) => {
            const li = document.createElement('li');
            li.innerText=data['message'];
            ul.appendChild(li);
            console.log(data['message']);
        });
    
        document.getElementById("subject_form").reset();

});

