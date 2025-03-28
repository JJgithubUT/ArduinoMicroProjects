// Importar Firebase
import { initializeApp } from "https://www.gstatic.com/firebasejs/9.6.1/firebase-app.js";
import { getDatabase, ref, onValue, set } from "https://www.gstatic.com/firebasejs/9.6.1/firebase-database.js";

// Configuración de Firebase
const firebaseConfig = {
  apiKey: "AIzaSyCRJuyByM4TGdBzFgaMQ7wsZ5OHdUc2Ujo",
  authDomain: "arduinoclase-a2019.firebaseapp.com",
  databaseURL: "https://arduinoclase-a2019-default-rtdb.firebaseio.com",
  projectId: "arduinoclase-a2019",
  storageBucket: "arduinoclase-a2019.firebasestorage.app",
  messagingSenderId: "80980411485",
  appId: "1:80980411485:web:fa6556a4d90f77683d79b4"
};

// Inicializar Firebase
const app = initializeApp(firebaseConfig);
const db = getDatabase(app);
const estadoRef = ref(db, "encendido");

// Elementos del DOM
const botonEncender = document.getElementById("botonEncender");
const solLuna = document.getElementById("solLuna");

// Escuchar cambios en Firebase y actualizar la UI
onValue(estadoRef, (snapshot) => {
  const encendido = snapshot.val();
  
  if (encendido) {
    botonEncender.classList.add("activo");
    solLuna.classList.add("luna");
  } else {
    botonEncender.classList.remove("activo");
    solLuna.classList.remove("luna");
  }
});

// Cambiar estado en Firebase al hacer clic en el botón
botonEncender.addEventListener("click", () => {
  onValue(estadoRef, (snapshot) => {
    const encendido = snapshot.val();
    set(estadoRef, !encendido); // Cambia el estado en Firebase
  }, { onlyOnce: true }); // Evita múltiples lecturas al hacer clic
});
