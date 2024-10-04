 
<h1 align="center">Sensor de Quedas: Tecnologia Vestível para Idosos Protótipo Eletrônico de Detecção de Quedas</h1>

<div align="center" >

![Badge em Desenvolvimento](http://img.shields.io/static/v1?label=STATUS&message=FINALIZADO&color=GREEN&style=for-the-badge)
![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![arduino](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![GitHub Org's stars](https://img.shields.io/github/stars/and3510?style=social)

</div>

## Sumário

* [Introdução](#Introdução)
* [Componentes usados no Prototipo](#Componentes-usados-no-Prototipo)
* [Desenvolvimento do Programa](#Desenvolvimento-do-Programa)
* [Resultados Obtidos](#Resultados-Obtidos)
* [Como_Usar](#Como_Usar)
* [Conclusão](#conclusão)

## Introdução
Para esse bimestre, nós tínhamos que trabalhar com hardware e software, enquanto simultaneamente continuamos nosso projeto voltado para idosos, então decidimos fazer um protótipo de sensor de queda, a fim de aproveitar as funcionalidades do Arduino para beneficiar os idosos para terem melhor segurança e bem-estar. Apesar das dificuldades encontradas durante o desenvolvimento do protótipo, conseguimos um bom resultado, através de uma pesquisa extensiva, explorando documentos, artigos científicos e vídeos.

---

## Componentes usados no Prototipo 

<div align="center" >

<img width="500px" src="./images/fake.png"  alt="GitHub Readme Stats" />

<br>

<img width="500px" src="/home/anderson/coders_folders/arduino/projects_arduinos/projeto_alarme_quedas/images/IMG_20240108_222757.jpg"  alt="GitHub Readme Stats" />

</div>

- Buzzer 5v -> Para aviso sonoro.
- Protoboard de 300 pinos -> Usado para expandir as conecçoes entre os compoenentes e usar como base do prototipo.
- Arduino Uno -> Um Microcontrolador, onde armazena um nosso codigo e processa todas as tarefas.
- MPU-6050 -> É um acelerômetro e giroscópio capaz de medir a aceleração e rotação nos três eixos coordenados (x,y,z).
- Bateria 9v -> Fonte de energia do dispositivo.

---

## Desenvolvimento do Programa

<div align="center" >

<img width= "500px" src="./images/code.png" alt="GitHub Readme Stats" /> 

</div>

<p>Parte do codigo</p>

- O programa analisa os dados do mpu6050 e calcula atraves da aceleraçao o movimento brusco e o angulo do dispositivo.
- O codigo funciona com dois estagios para detecçao de queda.
  - 1º Estagio verifica a condiçao de movimento brusco.
  - 2º Estagio verifica a condiçao de uma real queda.


---

## Resultados Obtidos 

<div align="center" >

<img width= "450px" src="./images/real.png" alt="GitHub Readme Stats" /> 

</div>

Aqui está uma versão aprimorada da frase para o README, com uma linguagem mais formal e clara:

---

## Como_Usar

> Além do hardware, é necessário o software para executar o programa no microcontrolador.

### 1. Instale o Arduino IDE

- Acesse o site oficial do [Arduino](https://www.arduino.cc/) e faça o download da IDE.
- Inicie o Programa

<div align="center">

<img width="600px" src="./images/image10.png" alt="GitHub Readme Stats" /> 

</div>




### 2. Abra o Arquivo

Na plataforma Arduino IDE, abra o arquivo localizado na pasta correspondente ao projeto.

<div align="center">

<img width="300px" src="./images/image.png" alt="GitHub Readme Stats" /> 

</div>

### 3. Configurações

- Ao tentar rodar o script no Arduino UNO, caso a plataforma sugira configurações adicionais, aceite as recomendações fornecidas.

- Selecione a placa conectada ao computador

<div align="center">

<img width="550px" src="./images/image12.png" alt="GitHub Readme Stats" /> 

</div>

---


### 4. Pronto! click em Upload para Placa

<div align="center">

<img width="550px" src="./images/image11.png" alt="GitHub Readme Stats" /> 

</div>


## Conclusão

O protótipo de sensor de queda para idosos uniu hardware e software, utilizando o Arduino Uno e o sensor MPU-6050 para detectar movimentos bruscos e quedas reais. Apesar dos desafios técnicos, o projeto alcançou bons resultados, mostrando potencial para melhorar a segurança e qualidade de vida dos idosos. As próximas etapas envolvem possíveis melhorias e refinamentos do dispositivo.
