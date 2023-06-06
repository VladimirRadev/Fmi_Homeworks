const registrationForm=document.getElementById('registration-form');
registrationForm.addEventListener('submit', (event)=> {
    const username = document.getElementById('username');
    const name = document.getElementById('name');
    const email = document.getElementById('email');
    const password = document.getElementById('password');
    const street = document.getElementById('street');
    const city = document.getElementById('city');
    const postalCode = document.getElementById('postal-code');
    const invalidDataError= document.getElementById('invalid-data');
    const existingUserError= document.getElementById('existing-user');
    const successMessage= document.getElementById('success');
    
    fetch('https://jsonplaceholder.typicode.com/users') 
        .then ((response) =>  {
            return response.json();
        })
        .then((registratedUsers) => {
            successMessage.innerText="";
            if(!(username.value.length >= 3 && username.value.length <=10)){
                invalidDataError.innerText='Невалидно потребителско име. Трябва да е между 3 и 10 символа'
                return;
            }
            if(!(name.value.length >= 1 && name.value.length <= 50)){
                invalidDataError.innerText='Невалидно име. Трябва да е максимум 50 символа';
                return;

                
            }
            const emailPattern = new RegExp("[a-z0-9_]+@[a-z]+\.[a-z]+");
            if(!emailPattern.test(email.value)){
                invalidDataError.innerText='Невалиден имейл.';
          
                return;
                
            }
            var passwordPattern = /^(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{6,10}$/;
            
            if(!passwordPattern.test(password.value)){
                invalidDataError.innerText='Невалидна парола. Трябва да съдържа главна и малка буква , както и цифра и общата и дължина да е между 6 и 10 символа. ';
                return;
            }
            var postalCodePattern1= /^\d{5}\-\d{4}$/;
            var postalCodePattern2 = /^\d{4}$/;
            
            if(postalCode.value !== "") {
            if(!(postalCodePattern1.test(postalCode.value) || postalCodePattern2.test(postalCode.value) )){
                invalidDataError.innerText='Невалиден пoщенски код. Трябва да е ддддд-дддд или дддд където д е цифра.';
                return;
            }
            }
            invalidDataError.innerText="";

            let alreadyExist=false;
            registratedUsers.forEach(registratedUser => {
                if (registratedUser["username"] === username.value){
                    alreadyExist=true;
                }
            });            
            if (alreadyExist===true){
                existingUserError.innerText='Вече съществува потребител с такова потребителско име. Пробвайте с нещо различно.';
                return;
            }

            existingUserError.innerText="";

            successMessage.innerText="Вие успешно се регистрирахте !";

        });
    
    event.preventDefault();
});   