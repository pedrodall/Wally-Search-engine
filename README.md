# Wally-Search-engine
miniwally: https://drive.google.com/drive/folders/1N7Vr1UagZ9J8Wk3JsNO4aVgH-1Qa6X8N?usp=sharing
Wallyserver: https://drive.google.com/drive/folders/1L8QXBdYM5uX_sSt4l12jcAU_HIA2M_b6?usp=sharing

-Implementação Web:

----Pelo Linux (no nosso caso, fizemos a implementação web em uma VirtualBox em Ubuntu 64bits): 

  Instale a biblioteca Boost pelo terminal com o comando...

  sudo apt-get install libssl-dev libboost-filesystem-dev libboost-thread-dev

  Após instalar, baixe nossa pasta no Google Drive chamada "Wallyserver" para rodar a pesquisa com o database inteiro ou baixe a pasta miniwally para rodar nossa pesquisa web com o database limitado.
  Abra o terminal na pasta Wallyserver e rode o executável wallyserver.out ou crie um exécutável com o comando...
  
  g++ wallyserver.cpp -I/usr/include -lboost_filesystem -lboost_thread -lpthread -o wallyserver.out -o nomeexecutavel.out
  
  Quando a desserialização acabar, abra o link "http://localhost:8080/mainpage.html" no seu navegador e se divirta.
  
----Pelo macOS:

  Aprendemos pelo monitor a apenas instalar tudo pelo Linux, mas o criador da Boost diz que para baixar a biblioteca pelo macOS deve-se rodar o comando...
  
  brew install openssl boost

Após instalar, baixe nossa pasta no Google Drive chamada "Wallyserver" para rodar a pesquisa com o database inteiro ou baixe a pasta miniwally para rodar nossa pesquisa web com o database limitado.
  Abra o terminal na pasta Wallyserver e rode o executável wallyserver.out ou crie um exécutável com o comando...
  
  g++ wallyserver.cpp -I/usr/include -lboost_filesystem -lboost_thread -lpthread -o wallyserver.out -o nomeexecutavel.out
  
  Quando a desserialização acabar, abra o link "http://localhost:8080/mainpage.html" no seu navegador e se divirta.
  
