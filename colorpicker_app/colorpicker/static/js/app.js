
// https://stackoverflow.com/questions/35549547/fetch-api-vs-xmlhttprequest
// https://hacks.mozilla.org/2015/03/this-api-is-so-fetching/
// https://stackoverflow.com/questions/45018338/javascript-fetch-api-how-to-save-output-to-variable-as-an-object-not-the-prom

// asignaciones en features funcionales de javascrip vanilla js 
/*fetch('https://jsonplaceholder.typicode.com/posts/1')
.then(res => res.json())
.then(data => obj = data)
.then(() => console.log(obj))*/


const peticionarioMovimientos = new XMLHttpRequest();
const requestAPI = new XMLHttpRequest();


function isNumeric(str) {
    if (typeof str != "string") return false // we only process strings!  
    return !isNaN(str) && // use type coercion to parse the _entirety_ of the string (`parseFloat` alone does not do this)...
        !isNaN(parseFloat(str)) // ...and ensure strings of whitespace fail
}


function listaMovimientos() {
    const campos = ['fecha', 'hora', 'from_moneda', 'from_cantidad', 'to_moneda', 'to_cantidad'];
    let url = '/api/v1/movimientos';
    fetch(url).then((res) => { return res.json() })
        .then((movimientos) => {
            if (movimientos["status"] === "success") {
                movimientos["data"].forEach(function (movimiento) {
                    const tbody = document.querySelector("#tbbody-movimientos");
                    const fila = document.createElement('tr');
                    for (const campo of campos) {
                        const celda = document.createElement('td');
                        celda.innerHTML = movimiento[campo];
                        fila.appendChild(celda);
                    }
                    tbody.appendChild(fila);
                })
            } else if (movimientos["status"] === "fail") {
                alert(movimientos["mensaje"]);
            } else {
                alert("Se ha producido un error.");
            }
        });
}

function validar_inputs_tasa_cambio(from_moneda, to_moneda, cantidad_origen) {

    if (from_moneda === "default" || to_moneda === "default" || cantidad_origen === "") {
        alert("Por favor, rellene todos los campos señalados con un asterisco (*)");
        return false;
    }

    if (from_moneda === to_moneda) {
        alert("Las monedas de origen y destino deben ser diferentes.");
        return false;
    }
    if (parseFloat(cantidad_origen) <= 0 || cantidad_origen === null || !isNumeric(cantidad_origen)) {
        alert("Introduzca un número VÁLIDO por favor.");
        return false;
    }


    return true;
}


function calcular_tasa_cambio() {
    var infoHTML = document.querySelector("#info");
    var from_moneda = document.getElementById("moneda_origen").value;
    var to_moneda = document.getElementById("moneda_destino").value;
    var cantidad_origen = document.getElementById("cantidad_origen").value;
    var inputs_ok = validar_inputs_tasa_cambio(from_moneda, to_moneda, cantidad_origen);

    if (inputs_ok) {
        let url = "/api/v1/tipo_cambio/" + from_moneda + "/" + to_moneda + "/" + cantidad_origen;
        fetch(url).then((res) => { return res.json() }).then(data => {
            if (data["status"] === "success") {
                document.getElementById("tasa").value = data["data"]["tipo_cambio"];
                var tasa = parseFloat(data["data"]["tipo_cambio"]);
                document.getElementById("tasa").value = tasa;
                var importe = parseFloat(document.getElementById("cantidad_origen").value);
                document.getElementById("cantidad_destino").value = tasa * importe;
                document.getElementById("cantidad_origen").disabled = true;

            } else if (data["status"] === "fail") {
                alert(data["mensaje"]);
            } else {
                alert("Ups...Se ha producido un error en la consulta.");
            }
        });
    } else {
        // TODO
    }
}

function confirmar() {
    const from_moneda = document.getElementById("moneda_origen").value;
    const to_moneda = document.getElementById("moneda_destino").value;
    const cantidad_origen = document.getElementById("cantidad_origen").value;
    const cantidad_destino = document.getElementById("cantidad_destino").value;
    var inputs_ok = validar_inputs_tasa_cambio(from_moneda, to_moneda, cantidad_origen);
    if (inputs_ok) {
        var url_nuevo_movimiento = '/api/v1/movimiento';
        const movimiento = {
            "from_moneda": from_moneda,
            "from_cantidad": cantidad_origen,
            "to_moneda": to_moneda,
            "to_cantidad": cantidad_destino
        };
        fetch(url_nuevo_movimiento, {
            method: 'POST',
            headers: {
                'Accept': 'application/json, text/plain, */*',
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(movimiento)
        }).then((res) => { return res.json() })
            .then(data => {
                if (data["status"] == "success") {
                    alert("Se ha grabado un nuevo movimiento correctamente!");
                } else if (data["status"] == "fail") {
                    alert(data["mensaje"]);
                } else {
                    alert("Se ha producido un error. Inténtelo en unos instantes.");
                }
            });
    }

}

function carga_status() {

    let url = "/api/v1/status";
    fetch(url).then((res) => { return res.json() }).then(data => {
        if (data["status"] == "success") {
            var invertido = data["data"]["invertido"];
            var valor_actual = data["data"]["valor_actual"];
            var resultado = valor_actual - invertido;
            document.getElementById("eur_invertidos").value = parseFloat(invertido).toFixed(2);
            document.getElementById("valor_criptos_eur").value = parseFloat(valor_actual).toFixed(2);
            document.getElementById("resultado").value = parseFloat(resultado).toFixed(2);
            if (resultado < 0) {
                document.getElementById("resultado").style.color = "red";
            }
        } else if (data["status"] == "fail") {
            alert(data["mensaje"]);
        } else {
            alert("Se ha producido un error. Inténtelo en unos instantes.");
        }
    });
}


