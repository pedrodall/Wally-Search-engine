function query(){
	//Obtenho o texto digitado pelo usuário
	const text_query = document.getElementById("pesquisa").value;
	//URL que farei a query para o servidor
	const URL = "http://localhost:8080/query?text="+text_query;

	//Acesso o URL "escondido", sem atualizar a página atual
	fetch(URL)
		.then(function (response) {  //e "então", executo essa função com a resposta do URL
				return response.json();
			  })
		//chamamos esse "response.json()" de "data" e alteramos o q está escrito na tag de ig "output"
		.then(function (data) {
				document.getElementById("div0").innerHTML = data.res;
				document.getElementById("div1").innerHTML = data.teste0;
				document.getElementById("div2").innerHTML = data.teste1;
				document.getElementById("div3").innerHTML = data.teste2;
				document.getElementById("div4").innerHTML = data.teste3;
				document.getElementById("div5").innerHTML = data.teste4;
				document.getElementById("div6").innerHTML = data.teste5;
				document.getElementById("div7").innerHTML = data.teste6;
				document.getElementById("div8").innerHTML = data.teste7;
				document.getElementById("div9").innerHTML = data.teste8;
				document.getElementById("div10").innerHTML = data.teste9;
				document.getElementById("div11").innerHTML = data.teste10;
				document.getElementById("div12").innerHTML = data.teste11;
				document.getElementById("div13").innerHTML = data.teste12;
				document.getElementById("div14").innerHTML = data.teste13;
				document.getElementById("div15").innerHTML = data.teste14;
				document.getElementById("div16").innerHTML = data.teste15;
				document.getElementById("div17").innerHTML = data.teste16;
				document.getElementById("div18").innerHTML = data.teste17;
				document.getElementById("div19").innerHTML = data.teste18;
				document.getElementById("div20").innerHTML = data.teste19;


				document.getElementById("wally").innerHTML ="";
				document.getElementById("aba").innerHTML = "<form onsubmit=\'return false\' method=\'get\'> <a id=\'minilogo\' href=\'mainpage.html\'> <img src=\'waldinho.png\' width=10% height=10%></a><label for=\'pesquisa2\'> Mais alguma coisa? </label><input type=\'text\' id=\'pesquisa2\' required><input id=\'btn\' type=\'button\'  onclick=\'query2()\' value=\'Ok\'></form>";
			  })
}

function query2(){
	//Obtenho o texto digitado pelo usuário
	const text_query = document.getElementById("pesquisa2").value;
	//URL que farei a query para o servidor
	const URL = "http://localhost:8080/query?text="+text_query;

	//Acesso o URL "escondido", sem atualizar a página atual
	fetch(URL)
		.then(function (response) {  //e "então", executo essa função com a resposta do URL
				return response.json();
			  })
		//chamamos esse "response.json()" de "data" e alteramos o q está escrito na tag de ig "output"
		.then(function (data) {
				document.getElementById("div0").innerHTML = data.res;
				document.getElementById("div1").innerHTML = data.teste0;
				document.getElementById("div2").innerHTML = data.teste1;
				document.getElementById("div3").innerHTML = data.teste2;
				document.getElementById("div4").innerHTML = data.teste3;
				document.getElementById("div5").innerHTML = data.teste4;
				document.getElementById("div6").innerHTML = data.teste5;
				document.getElementById("div7").innerHTML = data.teste6;
				document.getElementById("div8").innerHTML = data.teste7;
				document.getElementById("div9").innerHTML = data.teste8;
				document.getElementById("div10").innerHTML = data.teste9;
				document.getElementById("div11").innerHTML = data.teste10;
				document.getElementById("div12").innerHTML = data.teste11;
				document.getElementById("div13").innerHTML = data.teste12;
				document.getElementById("div14").innerHTML = data.teste13;
				document.getElementById("div15").innerHTML = data.teste14;
				document.getElementById("div16").innerHTML = data.teste15;
				document.getElementById("div17").innerHTML = data.teste16;
				document.getElementById("div18").innerHTML = data.teste17;
				document.getElementById("div19").innerHTML = data.teste18;
				document.getElementById("div20").innerHTML = data.teste19;
				document.getElementById("wally").innerHTML ="";
				document.getElementById("aba").innerHTML = "<form onsubmit=\'return false\' method=\'get\'> <a id=\'minilogo\' href=\'mainpage.html\'> <img src=\'waldinho.png\' width=10% height=10%></a><label for=\'pesquisa2\'> Mais alguma coisa? </label><input type=\'text\' id=\'pesquisa2\' required><input id=\'btn\' type=\'submit\' onclick=\'query2()\' value=\'Ok\'></form>";
			  })
}

function mais20(){
	const text_query = document.getElementById("pesquisa").value;
	const URL = "http://localhost:8080/query?text="+text_query;
	fetch(URL)
		.then(function (response) {  
				return response.json();
			  })
		.then(function (data) {
			
				document.getElementById("div0").innerHTML = data.res;
				document.getElementById("div1").innerHTML = data.teste0;
				document.getElementById("div2").innerHTML = data.teste1;
				document.getElementById("div3").innerHTML = data.teste2;
				document.getElementById("div4").innerHTML = data.teste3;
				document.getElementById("div5").innerHTML = data.teste4;
				document.getElementById("div6").innerHTML = data.teste5;
				document.getElementById("div7").innerHTML = data.teste6;
				document.getElementById("div8").innerHTML = data.teste7;
				document.getElementById("div9").innerHTML = data.teste8;
				document.getElementById("div10").innerHTML = data.teste9;
				document.getElementById("div11").innerHTML = data.teste10;
				document.getElementById("div12").innerHTML = data.teste11;
				document.getElementById("div13").innerHTML = data.teste12;
				document.getElementById("div14").innerHTML = data.teste13;
				document.getElementById("div15").innerHTML = data.teste14;
				document.getElementById("div16").innerHTML = data.teste15;
				document.getElementById("div17").innerHTML = data.teste16;
				document.getElementById("div18").innerHTML = data.teste17;
				document.getElementById("div19").innerHTML = data.teste18;
				document.getElementById("div20").innerHTML = data.teste19;

}



function print_img(){
	const image_div = document.getElementById("image"); //Acesso a div que quero inserir a imagem
	const image_obj = document.createElement("img"); //Crio uma tag vazia <img></img>
	image_obj.src = "pokemon.jpeg"; //Altero o atributo "src", que é o endereço da imagem
	image_div.appendChild(image_obj); //Insiro a tag criada dentro da <div id ="image"></div>
}