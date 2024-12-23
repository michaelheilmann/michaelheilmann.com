/* Copyright (c) 2024 Michael Heilmann. All rights reserved. */
@@media not print {
  :root {
    --black: rgb(3,3,3);
    --white: rgb(252,252,252);
    --blue: #0044CC;
  }
}
@@media print {
  :root {
    --black: black;
    --white: white;
    --blue: #0044CC;
  }
}

a {
  color: var(--blue);
}

/*
landing page font (if font style "normal" is used)
https://developer.mozilla.org/en-US/docs/Web/CSS/@@font-face/font-weight
*/
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-Thin.ttf');
  font-weight: 100;
  font-style: normal;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-ExtraLight.ttf');
  font-weight: 200;
  font-style: normal;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-Light.ttf');
  font-weight: 300;
  font-style: normal;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-Regular.ttf');
  font-weight: 400;
  font-style: normal;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-Medium.ttf');
  font-weight: 500;
  font-style: normal;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-SemiBold.ttf');
  font-weight: 600;
  font-style: normal;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-Bold.ttf');
  font-weight: 700;
  font-style: normal;
}

/*
landing page font (if font style "italic" is used)
https://developer.mozilla.org/en-US/docs/Web/CSS/@@font-face/font-weight
*/
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-ThinItalicItalic.ttf');
  font-weight: 100;
  font-style: italic;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-ExtraLightItalic.ttf');
  font-weight: 200;
  font-style: italic;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-LightItalic.ttf');
  font-weight: 300;
  font-style: italic;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-RegularItalic.ttf');
  font-weight: 400;
  font-style: italic;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-MediumItalic.ttf');
  font-weight: 500;
  font-style: italic;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-SemiBoldItalic.ttf');
  font-weight: 600;
  font-style: italic;
}
@@font-face {
  font-family: 'my-landing-page-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans/static/NotoSans-BoldItalic.ttf');
  font-weight: 700;
  font-style: italic;
}

/*
default font (if font style "normal" is used)
https://developer.mozilla.org/en-US/docs/Web/CSS/@@font-face/font-weight
*/
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-Thin.ttf');
  font-weight: 100;
  font-style: normal;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-ExtraLight.ttf');
  font-weight: 200;
  font-style: normal;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-Light.ttf');
  font-weight: 300;
  font-style: normal;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-Regular.ttf');
  font-weight: 400;
  font-style: normal;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-Medium.ttf');
  font-weight: 500;
  font-style: normal;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-SemiBold.ttf');
  font-weight: 600;
  font-style: normal;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-Bold.ttf');
  font-weight: 700;
  font-style: normal;
}

/*
default font (if font style "italic" is used)
https://developer.mozilla.org/en-US/docs/Web/CSS/@@font-face/font-weight
*/
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-ThinItalicItalic.ttf');
  font-weight: 100;
  font-style: italic;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-ExtraLightItalic.ttf');
  font-weight: 200;
  font-style: italic;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-LightItalic.ttf');
  font-weight: 300;
  font-style: italic;
}
@@font-face {
  font-family: 'my-default-font';
  /* Unsure why there is no "RegularItalic". */
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-MediumItalic.ttf');
  font-weight: 400;
  font-style: italic;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-MediumItalic.ttf');
  font-weight: 500;
  font-style: italic;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-SemiBoldItalic.ttf');
  font-weight: 600;
  font-style: italic;
}
@@font-face {
  font-family: 'my-default-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Serif/static/NotoSerif-BoldItalic.ttf');
  font-weight: 700;
  font-style: italic;
}

/*
default code font
*/
@@font-face {
  font-family: 'my-code-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans_Mono/static/NotoSansMono-ThinItalic.ttf');
  font-weight: 100;
  font-style: normal;
}
@@font-face {
  font-family: 'my-code-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans_Mono/static/NotoSansMono-ExtraLight.ttf');
  font-weight: 200;
  font-style: normal;
}
@@font-face {
  font-family: 'my-code-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans_Mono/static/NotoSansMono-Light.ttf');
  font-weight: 300;
  font-style: normal;
}
@@font-face {
  font-family: 'my-code-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans_Mono/static/NotoSansMono-Regular.ttf');
  font-weight: 400;
  font-style: normal;
}
@@font-face {
  font-family: 'my-code-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans_Mono/static/NotoSansMono-Medium.ttf');
  font-weight: 500;
  font-style: normal;
}
@@font-face {
  font-family: 'my-code-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans_Mono/static/NotoSansMono-SemiBold.ttf');
  font-weight: 600;
  font-style: normal;
}
@@font-face {
  font-family: 'my-code-font';
  src: url('https://michaelheilmann.com/assets/noto-new/Noto_Sans_Mono/static/NotoSansMono-Bold.ttf');
  font-weight: 700;
  font-style: normal;
}


html.my-theme-1 {
  font-family: 'my-default-font';
  color: var(--black);
  background-color: var(--white);
}

html.my-theme-1 code {
  font-family: 'my-code-font';
  color: var(--black);
  background-color: var(--white);
  font-weight: thin;
  font-size: 0.9rem;
}

/* Style for the index and the error page. */
body.my-index-page-1, body.my-error-page {
  font-family: 'my-landing-page-font';
  font-size: 2rem;
  display: flex;
  flex-direction: column;
  min-width: max(64rem, 100vw);
  min-height: max(32rem, 100vh);
  width: max(64rem, 100vw);
  height: max(32rem, 100vh);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

body.my-content-page-1 {
  margin: 16px;
  margin-left: 0px;
  margin-right: 0px;
  margin-top: 0px;
}

body.my-error-page-1 header, body.my-content-page-1 header {
  background-color: var(--black);
  /*min-height: 16px;*/
  display: flex;
  flex-direction: row;
  padding-left: 16px;
  padding-right: 16px;
  padding-top: 4px;
  padding-bottom: 4px;
}

body.my-error-page-1 header a, body.my-content-page-1 header a {
  text-decoration: none;
  color: var(--white);
}

body.my-content-page-1 main {
  margin-left: 16px;
  margin-right: 16px;
}

body.my-content-page-1 footer {
  border-top-style: solid;
  border-top-width: 1px;
  margin-top: 16px;
  padding-top: 16px;
}

body.my-content-page-1 ul li {
  margin-left: 1rem;
}

body.my-content-page-1 h2 {
  margin-top: 2rem;
  margin-bottom: 0.5rem;
}

body.my-content-page-1 h3 {
  margin-top: 1rem;
  margin-bottom: 0.5rem;
}

body.my-content-page-1 p {
  margin-top: 1rem;
}
