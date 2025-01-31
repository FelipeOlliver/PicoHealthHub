# PicoHealthHub
Sistema Embarcado portátil para monitoramento de sinais vitais, denominado "Pico Health Hub", utilizando a Raspberry Pi Pico W.
[![GitHub Issues](https://img.shields.io/github/issues/FelipeOlliver/PicoHealthHub?style=flat-square)](https://github.com/FelipeOlliver/PicoHealthHub/issues)
[![GitHub Pull Requests](https://img.shields.io/github/pulls/FelipeOlliver/PicoHealthHub?style=flat-square)](https://github.com/FelipeOlliver/PicoHealthHub/pulls)
[![GitHub License](https://img.shields.io/github/license/FelipeOlliver/PicoHealthHub?style=flat-square)](https://github.com/FelipeOlliver/PicoHealthHub/blob/main/LICENSE)

![pico_health_hub_circuito-1](https://github.com/user-attachments/assets/6adb1ea7-377a-4b33-a67c-158e00e31e46)


## Descrição

O **Pico Health Hub** é um sistema embarcado portátil de baixo custo, desenvolvido utilizando a plataforma Raspberry Pi Pico W, com o objetivo de monitorar sinais vitais e promover o autocuidado da saúde. Este projeto visa integrar múltiplos sensores e funcionalidades em um único dispositivo, proporcionando aos usuários a capacidade de coletar dados fisiológicos como pressão arterial, temperatura corporal, oximetria e sons cardíacos/respiratórios. Os dados são então armazenados na nuvem para acompanhamento e análise.

## Funcionalidades Principais

*   **Monitoramento de Sinais Vitais:**
    *   Medição da pressão arterial.
    *   Medição da temperatura corporal.
    *   Medição da saturação de oxigênio (SpO2).
    *   Auscultação de sons cardíacos e respiratórios.
*   **Interface com o Usuário:**
    *   Display OLED para exibição de informações e menus.
    *   Botões para navegação e seleção de opções.
    *   Joystick para controle.
    *   Feedback visual (LED RGB) e sonoro (buzzer).
*   **Conectividade:**
    *   Conexão Wi-Fi para comunicação com plataforma na nuvem.
    *   Suporte a teclado Bluetooth para entrada de dados.
*   **Armazenamento na Nuvem:**
    *   Armazenamento seguro dos dados coletados na nuvem.
    *   Acesso remoto aos dados para acompanhamento.
*   **Acessibilidade:**
    *   Design intuitivo e fácil de usar, mesmo para pessoas com pouca familiaridade com tecnologia.
    *   Utilização de componentes de baixo custo para democratização do acesso.

## Estrutura do Repositório
Pico-Health-Hub/
├── docs/ # Documentação do projeto
│ ├── academic_document.pdf # Documento acadêmico detalhado
│ └── ... # Outros documentos
├── hardware/ # Arquivos do projeto de hardware
│ ├── schematics/ # Arquivos de esquemáticos (Kicad)
│ │ └── PicoHealthHub.kicad_sch
│ ├── layouts/ # Arquivos de layout da PCB (Kicad)
│ │ └── ...
│ ├── bom.csv # Lista de materiais (BOM)
│ └── ...
├── firmware/ # Código fonte do firmware
│ ├── src/ # Código fonte em C/C++ (SDK Raspberry Pi Pico)
│ │ └── main.c
│ │ └── ...
│ ├── lib/ # Bibliotecas de código
│ │ └── ...
│ ├── include/ # Arquivos de cabeçalho
│ │ └── ...
│ ├── CMakeLists.txt # Arquivo CMake para compilação
│ └── ...
├── images/ # Imagens para o README e documentação
│ ├── pico_health_hub.png # Imagem principal do projeto
│ └── ...
├── LICENSE # Licença do projeto
└── README.md # Este arquivo README

## Como Executar o Projeto

### Requisitos

*   Raspberry Pi Pico W
*   Ambiente de desenvolvimento do Raspberry Pi Pico SDK
*   Componentes eletrônicos listados no arquivo `hardware/bom.csv`
*   Conhecimento básico de programação em C/C++ e eletrônica

### Passos

1.  Clone este repositório:

    ```bash
    git clone https://github.com/SEU_USUARIO/NOME_DO_REPOSITORIO.git
    ```
2.  Configure o ambiente de desenvolvimento do Raspberry Pi Pico SDK.
3.  Compile o código do firmware:

    ```bash
    cd firmware
    mkdir build
    cd build
    cmake ..
    make
    ```
4.  Gere o arquivo `.uf2` para carregar na placa.
5.  Construa o hardware seguindo os esquemáticos em `hardware/schematics`.
6.  Conecte os periféricos ao Raspberry Pi Pico W.
7.  Carregue o arquivo `.uf2` na placa Raspberry Pi Pico W.

## Documentação

A documentação completa do projeto, incluindo o relatório acadêmico detalhado, pode ser encontrada no diretório `docs/`.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues para relatar bugs ou sugerir melhorias, e para criar pull requests para contribuir com o desenvolvimento do projeto.

## Licença

Este projeto é distribuído sob a licença [MIT License](https://github.com/SEU_USUARIO/NOME_DO_REPOSITORIO/blob/main/LICENSE). Consulte o arquivo `LICENSE` para mais detalhes.

## Contato

*   Felipe de Oliveira Gomes
*   [felipedeoliveiragomes01@gmail.com]

---
