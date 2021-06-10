let tokenN = null;

function ispisi(error, token) {
    tokenN = token;
    if (!error) console.log(token);
}

function getAccessToken(proslijedi) {
    var ajax = new XMLHttpRequest();

    ajax.onreadystatechange = function () { // Anonimna funkcija
        if (ajax.readyState == 4 && ajax.status == 200)
            proslijedi(null, JSON.parse(ajax.responseText).access_token);
        else if (ajax.readyState == 4)
            proslijedi(ajax.status, null);
    }
    ajax.open("POST", "https://bitbucket.org/site/oauth2/access_token", false);
    ajax.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    ajax.setRequestHeader("Authorization", 'Basic ' + btoa("vDaEQRHauSnWXr5epH:wWWCYLgntz72usGkb5u2FpVBUEESzbsJ"));
    ajax.send("grant_type=" + encodeURIComponent("client_credentials"));
}


function listRepositories(error, token) {
    if (error) throw error;
    var ajax = new XMLHttpRequest();
    ajax.onreadystatechange = function () {
        if (ajax.readyState == 4 && ajax.status == 200) {
            let objekti = JSON.parse(ajax.responseText).values;
            var d_nested = document.getElementById("tabela");
            if (d_nested !== null && document.querySelector("body").contains(d_nested)) document.querySelector("body")
                .removeChild(d_nested);

            tbl = document.createElement("table");
            tbl.setAttribute("id", "tabela");

            row = document.createElement("tr");
            cell = document.createElement("th");
            cellText = document.createTextNode("Repozitoriji");
            cell.appendChild(cellText);
            row.appendChild(cell);
            tbl.appendChild(row);
            cell = document.createElement("th");
            cellText = document.createTextNode("Owner");
            cell.appendChild(cellText);
            row.appendChild(cell);
            tbl.appendChild(row);

            for (let i = 0; i < objekti.length; ++i) {
                row = document.createElement("tr");
                cell = document.createElement("td");
                cellText = document.createTextNode(objekti[i].name);
                cell.appendChild(cellText);
                row.appendChild(cell);
                cell = document.createElement("td");
                cellText = document.createTextNode(objekti[i].owner.username);
                cell.appendChild(cellText);
                row.appendChild(cell);
                tbl.appendChild(row);
            }
            document.querySelector("body").appendChild(tbl);
        } else if (ajax.readyState == 4)
            console.log(ajax.status);
    }
    ajax.open("GET", "https://api.bitbucket.org/2.0/repositories?role=member");
    ajax.setRequestHeader("Authorization", 'Bearer ' + token);
    ajax.send();
}

function odradiStvari() {
    getAccessToken(ispisi);
    if (tokenN != null) listRepositories(null, tokenN);
}

odradiStvari();