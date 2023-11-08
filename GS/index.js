function setFormMessage(formElement, message) {
    formElement.textContent = message;
}


document.addEventListener("DOMContentLoaded", () =>{
    const loginBox = document.querySelector("#submit");

    loginBox.addEventListener("submit", e =>{
        e.preventDefault();
        //Perform Fetch login
        setFormMessage(loginBox, "Invalid username/password combination");
})
})