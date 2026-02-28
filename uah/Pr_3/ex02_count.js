var hola = 'Hola desde Node.js'; // String 
var n_int = 1234; // Entero 
var n_float = 1.234; // Float
let count = 0;  
 
// Start interval  
const intervalId = setInterval(() => {  
  count++;  
  console.log(`Execution ${count}`);  
 
  // Stop after 5 executions  
  if (count === 5) {  
    clearInterval(intervalId);  
    console.log('Interval stopped after 5 executions!');  
  }  
}, 1000); 

// Una function
function add_ab (a,b){ 
    return (a+b); 
}

// Ejecucion del código
console.log(hola); 
console.log('Suma :' + n_int + ' + ' + n_float + ' = ' + add_ab(n_int,n_float));
