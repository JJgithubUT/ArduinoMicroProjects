import { initializeApp } from "https://www.gstatic.com/firebasejs/10.10.0/firebase-app.js";
import { getDatabase, ref, get, set } from "https://www.gstatic.com/firebasejs/10.10.0/firebase-database.js";

const firebaseConfig = {
    apiKey: "AIzaSyCRJuyByM4TGdBzFgaMQ7wsZ5OHdUc2Ujo",
    authDomain: "arduinoclase-a2019.firebaseapp.com",
    databaseURL: "https://arduinoclase-a2019-default-rtdb.firebaseio.com",
    projectId: "arduinoclase-a2019",
    storageBucket: "arduinoclase-a2019.firebasestorage.app",
    messagingSenderId: "80980411485",
    appId: "1:80980411485:web:fa6556a4d90f77683d79b4"
};

const app = initializeApp(firebaseConfig);
const db = getDatabase(app);
const estadoRef = ref(db, "estado");

document.addEventListener("DOMContentLoaded", () => {
    const boton = document.getElementById("botonEncender");
    const solLuna = document.getElementById("solLuna");
    const iconoSolLuna = solLuna.querySelector("i");

    get(estadoRef).then((snapshot) => {
        if (snapshot.exists()) {
            actualizarEstado(snapshot.val());
        } else {
            set(estadoRef, false);
            actualizarEstado(false);
        }
    });

    boton.addEventListener("click", () => {
        get(estadoRef).then((snapshot) => {
            const nuevoEstado = !snapshot.val();
            set(estadoRef, nuevoEstado);
            actualizarEstado(nuevoEstado);
        });
    });

    function actualizarEstado(estado) {
        if (estado) {
            boton.classList.add("activo");
            solLuna.classList.add("luna");
            iconoSolLuna.classList.replace("fa-sun", "fa-moon");
            boton.textContent = "消";
        } else {
            boton.classList.remove("activo");
            solLuna.classList.remove("luna");
            iconoSolLuna.classList.replace("fa-moon", "fa-sun");
            boton.textContent = "付";
        }
    }
});