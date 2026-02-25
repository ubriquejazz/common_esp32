var hola = 'Hola desde Node.js'; // String 
var n_int = 1234; // Entero 
var n_float = 1.234; // Float

// Una function
function add_ab (a,b){ 
    return (a+b); 
}

// Ejecucion del código
console.log(hola); 
console.log('Suma :' + n_int + ' + ' + n_float + ' = ' + add_ab(n_int,n_float));