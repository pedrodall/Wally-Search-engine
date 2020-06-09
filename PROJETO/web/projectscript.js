function query(){
	window.value = 0;
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
				document.querySelector("link[href='cssmainpage.css']").href = "cssquery.css";
				document.getElementById("wally").innerHTML ="";
				document.getElementById("atual").innerHTML = text_query;
				document.getElementById("textoprépag").innerHTML="Número de páginas encontradas por Wally:";
				document.getElementById("páginas").innerHTML = data.pag;
				document.getElementById("páginaatual").innerHTML = "Página atual:"+(window.value+1)+"/"+data.pag;
				for (var i = 1; i < 21 ; i++){
					if(data.pesquisas[i-1] != null){
						document.getElementById("div"+i).innerHTML=data.pesquisas[i-1];
					}
					else{document.getElementById("div"+i).innerHTML=""};	
				}

				document.getElementById("aba").innerHTML = "<main><form onsubmit=\'return false\' method=\'get\'> <a id=\'minilogo\' href=\'mainpage.html\'><img src=\'waldinho.png\' width=10% height=10%></a><label for=\'pesquisa2\' class=\'text-white\'> Mais alguma coisa? </label><input type=\'text\' id=\'pesquisa2\' autofocus required><input id=\'btn\' type=\'submit\' onclick=\'query2()\' value=\'Ok\'></form></main>";
			  	document.getElementById("setas").innerHTML = "<div class=\'botao\'><input id=\'menos20\' type=\'button\' onclick=\'menosvt()\' value=\'<-\'><input id=\'mais20\' type=\'button\' onclick=\'maisvt()\' value=\'->\'></div>"
			  })
}

function query2(){
	window.value = 0;
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

				document.getElementById("wally").innerHTML ="";
				document.getElementById("atual").innerHTML = text_query;
				document.getElementById("textoprépag").innerHTML="Número de páginas encontradas por Wally:";
				document.getElementById("páginas").innerHTML = data.pag;
				document.getElementById("páginaatual").innerHTML = "Página atual:"+(window.value+1)+"/"+data.pag;
				for (var i = 1; i < 21 ; i++){
					if(data.pesquisas[i-1] != null){
						document.getElementById("div"+i).innerHTML=data.pesquisas[i-1];
					}
					else{document.getElementById("div"+i).innerHTML=""};	
				}

				document.getElementById("aba").innerHTML = "<main><form onsubmit=\'return false\' method=\'get\'> <a id=\'minilogo\' href=\'mainpage.html\'><img src=\'waldinho.png\' width=10% height=10%></a><label for=\'pesquisa2\' class=\'text-white\'> Mais alguma coisa? </label><input type=\'text\' id=\'pesquisa2\' autofocus required><input id=\'btn\' type=\'submit\' onclick=\'query2()\' value=\'Ok\'></form></main>";
			  	document.getElementById("setas").innerHTML = "<div class=\'botao\'><input id=\'menos20\' type=\'button\' onclick=\'menosvt()\' value=\'<-\'><input id=\'mais20\' type=\'button\' onclick=\'maisvt()\' value=\'->\'></div>"
			  })
}

function expose(n,text_query){
	const URL = "http://localhost:8080/query?text="+text_query;

	//Acesso o URL "escondido", sem atualizar a página atual
	fetch(URL)
		.then(function (response) {  //e "então", executo essa função com a resposta do URL
				return response.json();
			  })
		//chamamos esse "response.json()" de "data" e alteramos o q está escrito na tag de ig "output"
		.then(function (data) {
			document.getElementById("páginaatual").innerHTML = "Página atual:"+(n+1)+"/"+data.pag;
				for (var i = 1; i < 21 ; i++){
					if(data.pesquisas[20*n+i-1] != null){
						document.getElementById("div"+i).innerHTML=data.pesquisas[20*n+i-1];
					}
					else{document.getElementById("div"+i).innerHTML="";};	
				}

			  })
}

function maisvt(){
	if(window.value < document.getElementById("páginas").innerHTML -1){
		window.value=window.value+1;
		const text_query = document.getElementById("atual").innerHTML;

		expose(window.value,text_query);
	}
}

function menosvt(){
	if(window.value>0){
		window.value=window.value-1;
		const text_query = document.getElementById("atual").innerHTML;
		expose(window.value,text_query);
	}
}

function print_img(){
	const image_div = document.getElementById("image"); //Acesso a div que quero inserir a imagem
	const image_obj = document.createElement("img"); //Crio uma tag vazia <img></img>
	image_obj.src = "pokemon.jpeg"; //Altero o atributo "src", que é o endereço da imagem
	image_div.appendChild(image_obj); //Insiro a tag criada dentro da <div id ="image"></div>
}
