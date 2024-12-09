# ArduinoAndGUI
Небольшой проект по работе Qt с платой arduino и LCD.
Короткая gif-ка, показывающая принцип работы

![](https://github.com/PopekaDS/ArduinoAndGUI/blob/main/sources/ArduinoAndGUI.gif)

Примечание: в gif есть небольшие проблемы, во-первых на экране должна показываться надпись "hello, world!", потому что я забыл включить-выключить плату. А во-вторых, я не мастер монтажа :), и может показаться, что после отправки надпись выводится с задержкой, но на самом деле это не так, просто кривой монтаж, прошу не судить строго

А вот как это всё выглядит в живую
![](https://github.com/PopekaDS/ArduinoAndGUI/blob/main/sources/ArduinoAndGUI.jpg)

**Принцип работы**
Сначала о работе платы
Заводим переменную checkScroll, которая отвечает за прокрутку экрана, если текст больше 16 символов. 
Первым байтом GUI нам сообщает, требуется ли прокрутка:
0 - значит экран стоит на месте
1 - значит требуется прокручивать экран

Потом идет считывание данных, вывод полученной строки на экран и отправка полученных символы обратно интерфейсу
