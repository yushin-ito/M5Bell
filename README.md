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

<h2>📝 Overview</h2>
<P>M5BellはM5StickCPlusを利用した研究室用インターホンです。鈴鹿高専の機械工学科の研究室の多くは、研究室の前に多目的室という部屋があります。研究室を訪れた際に、多目的室のドアをノックして反応がないと不在だと判断して諦めてしまうという事例が多く発生していていました。そこでこのインターホンを制作することにしました。</p>

<br>

<h2>🔧 Usage</h2>
<a href="https://open.vscode.dev/yushin-ito/M5Bell">
  <img src="https://img.shields.io/static/v1?logo=visualstudiocode&label=&message=Open%20in%20Visual%20Studio%20Code&labelColor=2c2c32&color=007acc&logoColor=007acc">
</a>
<br>
<br>
<ol>
  <li>リポジトリをクローンする</li>
  <p><pre><code>git clone https://github.com/yushin-ito/M5Bell</code></pre></p>
  <li>serverとclientをビルドする</li>
  <p><pre><code>platformio run</code></pre></p>
  <li>serverとclientを書き込む</li>
  <p><pre><code>platformio run --target upload</code></pre></p>
</ol>

<br>

<h2>🚀 Features</h2>
<p>通信方式はWebSocketを採用しました。親機(研究室側)をServer、子機(多目的室側)をClientとしています。<code>http://192.168.1.1</code>にアクセスすると管理画面を表示することができます。</p>
<br>
<ul>
  <li>
    <h3>インターホン</h3>
    <p>子機のボタンが押されるとWebSocketで<code>"request"</code>というテキストを送信します。テキストを受け取った親機は３つ選択肢から１つ選択してレスポンスを送信します。</p>
  </li>
  <br>
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yushin-ito/M5Bell/assets/75526539/d188e9d2-6e67-4f2c-a854-a293e3203734">
      <img src="https://github.com/yushin-ito/M5Bell/assets/75526539/a1c59262-c4ec-4b98-9133-2fd454ea6300">
  </picture>
  <br>
  <br>
  <li>
    <h3>ログ</h3>
    <p>Webサイトからログを確認することができます。</p>
  </li>
  <br>
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yushin-ito/M5Bell/assets/75526539/746ac0f3-d37e-4303-bd6f-08b5b92ecd93">
    <img src="https://github.com/yushin-ito/M5Bell/assets/75526539/f5715bb1-237d-41ea-9d6e-4f9cf9de0b8a">
  </picture>
  <br>
  <br>
  <li>
    <h3>時刻合わせ</h3>
    <p>WebサイトからWiFiを利用して時刻合わせをすることができます。</p>
  </li>
  <br>
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://github.com/yushin-ito/M5Bell/assets/75526539/9caa0e31-b912-4641-b6e1-0519e09d3cc2">
    <img src="https://github.com/yushin-ito/M5Bell/assets/75526539/a28720cc-a325-44c8-943e-7703d9ac882d">
  </picture>
</ul>

<img src="https://github.com/yushin-ito/M5Bell/assets/75526539/8f264307-a7af-4112-a6ae-04307f968b75">

<br>

<h2>👀 Author</h2>
<ul>
  <li>Yushin Ito</li>
  <li>Tatsuya Shirai</li>
</ul>

<br>

<h2>📜 License</h2>
<a href="https://github.com/yushin-ito/M5Bell/blob/main/LICENSE">MIT License<a>
