# **Monitor IoT de Energia Usando ESP32**

## **Visão Geral do Projeto**

Este projeto implementa um sistema IoT que monitora temperatura e intensidade luminosa utilizando o microcontrolador ESP32. Ele avalia condições ambientais para ajudar os usuários a determinar a viabilidade do uso de energia solar. Os dados dos sensores são enviados para a plataforma em nuvem **Thinger.io** , onde podem ser visualizados e analisados em tempo real por meio de dashboards.

## **Problema a Ser Resolvido**

A energia renovável, especialmente a solar, requer monitoramento ambiental preciso para otimizar o uso. Os usuários precisam de dados em tempo real sobre a intensidade luminosa e temperatura para tomar decisões informadas sobre a utilização de energia e melhorar a eficiência dos painéis solares. Este projeto atende a essa necessidade fornecendo:

- Monitoramento contínuo das condições ambientais.
- Visualização em tempo real em dashboards do **Thinger.io** .
- Recomendações para aprimorar a sustentabilidade energética.

## **Solução**

Integrando o ESP32 com um sensor de temperatura/umidade (DHT22) e um resistor dependente de luz (LDR), o sistema coleta, processa e carrega dados ambientais em uma plataforma em nuvem. Esta solução foi projetada para ser fácil de usar e escalável, permitindo o acesso aos dados de qualquer lugar com conexão à internet.

---

## **Tecnologias e Bibliotecas**

### **Hardware**

1. **ESP32** :

- Processador dual-core capaz de gerenciar Wi-Fi e Bluetooth.
- ADC integrado para leitura de dados analógicos dos sensores.
- Configurado para enviar requisições HTTP POST para o **Thinger.io** .

1. **Sensor DHT22** :

- Mede temperatura com alta precisão.
- Fornece saída digital.

1. **LDR** :

- Mede intensidade luminosa e gera uma tensão analógica.
- Conectado ao pino ADC do ESP32.

### **Software**

1. **Arduino IDE** :

- Utilizado para programar o ESP32.

1. **Thinger.io** :

- Plataforma em nuvem para visualização de dados IoT.

1. **Bibliotecas** :

- **`WiFi.h`** : Para conectividade Wi-Fi do ESP32.
- **`HTTPClient.h`** : Para comunicação HTTP com o Thinger.io.
- **`ArduinoJson.h`** : Para serialização JSON dos dados do sensor.
- **`DHT.h`** : Para interface com o sensor DHT22.

---

## **Como Funciona**

### **Explicação do Código**

1. **Conexão Wi-Fi** :

- A função **`connectWiFi()`** garante que o ESP32 se conecte à rede Wi-Fi. Caso desconectado, tenta reconectar.

1. **Leitura de Sensores** :

- A temperatura é lida pelo método **`dht.readTemperature()`** .
- A intensidade luminosa é medida lendo a tensão analógica no pino do LDR.

1. **Serialização de Dados** :

- Os valores dos sensores são convertidos para o formato JSON utilizando a biblioteca **`ArduinoJson`** .

1. **Transmissão de Dados via HTTP** :

- O ESP32 envia uma requisição POST com os dados JSON para a plataforma **Thinger.io** .

1. **Tratamento de Erros** :

- O código verifica a validade das leituras dos sensores e tenta reconexões em caso de falha nas requisições HTTP.

1. **Intervalo de Dados** :

- Os dados dos sensores são enviados a cada 5 segundos, permitindo atualizações em tempo real sem sobrecarregar o servidor.

### **Simulação**

- **Sensor DHT22** :
- Fornece leituras de temperatura em Celsius.
- Detecta e alerta em caso de falhas nas leituras.
- **Sensor LDR** :
- Fornece intensidade luminosa como valor analógico bruto.
- Útil para avaliar o potencial de energia solar.
- **Dashboard** :
- Os dados são visualizados no Thinger.io em tempo real.
- Inclui dados históricos e tendências para análise do usuário.

---

## **Recursos do Sistema**

### **Principais Funções**

1. **Monitoramento em Tempo Real** :

- Atualizações ao vivo de dados de temperatura e luz a cada 5 segundos.

1. **Integração com a Nuvem** :

- Usa HTTP para se comunicar com a plataforma Thinger.io.
- Dados acessíveis de qualquer lugar com internet.

1. **Visualização** :

- Dashboard interativo no Thinger.io mostra tendências, possibilitando decisões informadas.

1. **Tratamento de Erros** :

- Mecanismos robustos para lidar com erros de sensores e reconexão durante perda de Wi-Fi.

---

## **Vantagens**

1. **Insights Ambientais** :

- Fornece dados acionáveis para otimizar o uso de energia solar.

1. **Escalabilidade** :

- Pode ser expandido com sensores ou atuadores adicionais.
- Totalmente compatível com outras plataformas IoT, como MQTT ou Node-RED.

1. **Custo-Benefício** :

- Construído com componentes de baixo custo, como ESP32, DHT22 e LDR.

1. **Sustentabilidade** :

- Promove energia renovável, ajudando os usuários a avaliar o potencial da energia solar.

---

## **Instruções de Configuração**

### **Hardware**

1. Conecte o **sensor DHT22** :
   - VCC → ESP32 **`3V3`**
   - GND → ESP32 **`GND`**
   - DATA → ESP32 **`GPIO4`** (pino digital)
2. Conecte o **LDR** :
   - Um lado ao **`3V3`** e o outro a um resistor ligado ao pino **`ADC`** do ESP32 ( **`GPIO36`** ).

### **Software**

1. **Dependências** :

- Instale as seguintes bibliotecas via Arduino IDE:
  - **`DHT Sensor Library`**
  - **`ArduinoJson`**
  - **`WiFi`**
  - **`HTTPClient`**

1. **Envio de Código** :

- Configure as variáveis **`ssid`** e **`password`** com as credenciais do seu Wi-Fi.
- Defina o **`serverName`** com o endpoint do Thinger.io.
- Envie o código para o ESP32 usando o Arduino IDE.

1. **Configuração do Thinger.io** :

- Crie um bucket de dados para temperatura e luz.
- Projete um dashboard com widgets para visualizar os dados.

---

## **Exemplos Visuais**

### **Diagrama de Circuito**

### **Bucket de Dados no Thinger.io**

---

## **Principais Benefícios**

- **Fácil de Usar** : Simples de configurar e usar, com documentação abrangente.
- **Acessibilidade Remota** : Visualize dados ambientais de qualquer lugar.
- **Otimização Energética** : Ajuda os usuários a aproveitar ao máximo a energia solar.
- **Solução Escalável** : Integra facilmente sensores ou módulos adicionais para funcionalidades estendidas.

---

## **Conclusão**

Este projeto exemplifica como o IoT pode contribuir para a adoção de energia renovável e monitoramento ambiental. Aproveitando as capacidades do ESP32 e a robusta plataforma Thinger.io, ele oferece uma solução escalável e econômica para insights energéticos em tempo real.
