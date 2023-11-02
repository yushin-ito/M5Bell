<h1>M5Bell</h1>

<div align="left">
  <img src="https://img.shields.io/badge/version-1.0.0-red.svg">
  <img src="https://img.shields.io/github/actions/workflow/status/yushin-ito/M5Bell/server.yml?label=build(server)">
  <img src="https://img.shields.io/github/actions/workflow/status/yushin-ito/M5Bell/client.yml?label=build(client)">
  <img src="https://img.shields.io/github/stars/yushin-ito/M5Bell?color=yellow">
  <img src="https://img.shields.io/github/commit-activity/t/yushin-ito/M5Bell">
  <img src="https://img.shields.io/badge/license-MIT-green">
</div>

<br>

<h2>📝 M5Bellとは</h2>
<P>M5BellはM5StickCPlusを利用した研究室用インターホンです。鈴鹿高専の機械工学科の研究室の多くは、研究室の前に多目的室という部屋があります。研究室を訪れた際に、多目的室のドアをノックして反応がないと不在だと判断して諦めてしまうという事例が多く発生していていました。そこでこのインターホンを制作することにしました。</p>

<br>

<h2>👀 制作者</h2>
<ul>
  <li>Yushin Ito</li>
</ul>

<br>

<h2>🔧 ビルド</h2>
<a href="https://open.vscode.dev/yushin-ito/M5Bell">
  <img src="https://img.shields.io/static/v1?logo=visualstudiocode&label=&message=Open%20in%20Visual%20Studio%20Code&labelColor=2c2c32&color=007acc&logoColor=007acc">
</a>

<br>

<h2>🚀 機能</h2>
<p>通信方式はWebSocketを採用しました。親機(研究室側)をServer、子機(多目的室側)をClientとしています。http://192.168.1.1 にアクセスすると管理画面を表示することができます。</p>
<br>
<ul>
  <li>
    <h3>インターホン</h3>
    <p>子機のボタンが押されるとWebSocketで"request"というテキストを送信します。テキストを受け取った親機は３つ選択肢から１つ選択してレスポンスを送信します。</p>
  </li>
  <br>
  <div align="center">
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yushin-ito/M5Bell/assets/75526539/41f8a228-e465-42c2-b5a1-48dbbc69adfb">
      <img src="https://github.com/yushin-ito/M5Bell/assets/75526539/09f81e20-2331-4669-a9d0-7c50d7a3196c" width="80%">
    </picture>
  </div>
  <br>
  <br>
  <li>
    <h3>ログ</h3>
    <p>Webサイトからログを確認することができます。</p>
  </li>
  <br>
  <div align="center">
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yushin-ito/M5Bell/assets/75526539/57719a8a-866d-445b-a9b4-acd6cbd068b5">
      <img src="https://github.com/yushin-ito/M5Bell/assets/75526539/4f90a3ce-87a0-49b2-aa28-8bc7768cac16" width="80%">
    </picture>
  </div>
  <br>
  <br>
  <li>
    <h3>時刻合わせ</h3>
    <p>WebサイトからWiFiを利用して時刻合わせをすることができます。</p>
  </li>
  <br>
  <div align="center">
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yushin-ito/M5Bell/assets/75526539/5483e85e-f298-4f51-beb4-5671c12911d2">
    <img src="https://github.com/yushin-ito/M5Bell/assets/75526539/0b5d730f-5b7e-45e6-8fca-73d9d7c5f392" width="80%">
    </picture>
  </div>
</ul>

<br>

<h2>📜 ライセンス</h2>
<a href="https://github.com/yushin-ito/M5Bell/blob/main/LICENSE">MIT License<a>
