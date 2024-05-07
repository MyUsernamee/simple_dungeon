"use strict";(self.webpackChunkstackoverflow=self.webpackChunkstackoverflow||[]).push([[8825,1695],{26035:(e,t,n)=>{n.d(t,{JO:()=>i.Z,u_:()=>o.Z,zx:()=>r.Z});var r=n(39114),i=n(68472),o=(n(13354),n(21224),n(27416),n(26045),n(42576),n(5502))},67702:(e,t,n)=>{function r(e,t){return t?Array.isArray(t)?t.reduce(((e,t)=>t(e)),e):t(e):e}function i(e){return"[object Object]"===Object.prototype.toString.call(e)}function o(e){return Object.keys(e||{}).reduce(((t,n)=>Object.assign(Object.assign({},t),{[n]:i(e[n])?o(e[n]):Array.isArray(e[n])?[...e[n]]:e[n]})),{})}function a(e,t,n){e&&(e=o(e)),i(e)||(e={});const r=Array.isArray(t)?t:t.match(/[^.[\]]+/g)||[],a=r[r.length-1];if(!a)return e;let s=e;for(let e=0;e<r.length-1;e++){const t=r[e];if(!s[t]||!i(s[t])&&!Array.isArray(s[t])){const n=r[e+1];isNaN(Number(n))?s[t]={}:s[t]=[]}s=s[t]}return s[a]=n(s[a]),e}function s(e,t,n){const r=n=>String.prototype.split.call(t,n).filter(Boolean).reduce(((e,t)=>null!=e?e[t]:e),e),i=r(/[,[\]]+?/)||r(/[,[\].]+?/);return void 0===i||i===e?n:i}function u(e,t,n){return a(e,t,(()=>n))}function c(e){return"INPUT"===(null==e?void 0:e.nodeName)}function l(e){return"SELECT"===(null==e?void 0:e.nodeName)}function d(e){return"FIELDSET"===(null==e?void 0:e.nodeName)}function f(e){return c(e)||function(e){return"TEXTAREA"===(null==e?void 0:e.nodeName)}(e)||l(e)}function v(e){return e.nodeType===Node.ELEMENT_NODE}function y(e,t){return null!=t?t:f(e)?e.name:""}function p(e){if(f(e))return[e];if(0===e.childElementCount)return[];const t=new Set;for(const n of e.children){if(f(n)&&t.add(n),d(n))for(const e of n.elements)f(e)&&t.add(e);n.childElementCount>0&&p(n).forEach((e=>t.add(e)))}return Array.from(t)}function m(e){for(const t of e.elements)(f(t)||d(t))&&e.hasAttribute("data-felte-keep-on-remove")&&!t.hasAttribute("data-felte-keep-on-remove")&&(t.dataset.felteKeepOnRemove=e.dataset.felteKeepOnRemove)}function h(e){return e.type.match(/^(number|range)$/)?e.value?+e.value:null:e.value}function b(e){var t;let n={},r={};for(const i of e.elements){if(d(i)&&m(i),!f(i)||!i.name)continue;const o=y(i);if(c(i)){if("checkbox"===i.type){if(void 0===s(n,o)){if(1===Array.from(e.querySelectorAll(`[name="${i.name}"]`)).filter((e=>!!f(e)&&o===y(e))).length){n=u(n,o,i.checked),r=u(r,o,!1);continue}n=u(n,o,i.checked?[i.value]:[]),r=u(r,o,!1);continue}Array.isArray(s(n,o))&&i.checked&&(n=a(n,o,(e=>[...e,i.value])));continue}if("radio"===i.type){if(s(n,o))continue;n=u(n,o,i.checked?i.value:void 0),r=u(r,o,!1);continue}if("file"===i.type){n=u(n,o,i.multiple?Array.from(i.files||[]):null===(t=i.files)||void 0===t?void 0:t[0]),r=u(r,o,!1);continue}}else if(l(i)){if(i.multiple){const e=Array.from(i.selectedOptions).map((e=>e.value));n=u(n,o,e)}else n=u(n,o,i.value);r=u(r,o,!1);continue}const v=h(i);n=u(n,o,v),r=u(r,o,!1)}return{defaultData:n,defaultTouched:r}}function g(e,t){var n;if(!f(e))return;const r=t;if(c(e)){if("checkbox"===e.type){const t=r;return void 0===t||"boolean"==typeof t?void(e.checked=!!t):void(Array.isArray(t)&&(t.includes(e.value)?e.checked=!0:e.checked=!1))}if("radio"===e.type){const t=r;return void(e.value===t?e.checked=!0:e.checked=!1)}if("file"===e.type){if(t instanceof FileList)e.files=t;else if(t instanceof File&&"undefined"!=typeof DataTransfer){const n=new DataTransfer;n.items.add(t),e.files=n.files}else if("undefined"!=typeof DataTransfer&&Array.isArray(t)&&t.some((e=>e instanceof File))){const n=new DataTransfer;for(const e of t)e instanceof File&&n.items.add(e);e.files=n.files}else(!t||Array.isArray(t)&&!t.length)&&(e.files=null,e.value="");return}}else if(l(e)){if(e.multiple){if(Array.isArray(r)){e.value=String(null!==(n=r[0])&&void 0!==n?n:"");const t=r.map((e=>String(e)));for(const n of e.options)t.includes(n.value)?n.selected=!0:n.selected=!1}}else{e.value=String(null!=r?r:"");for(const t of e.options)t.value===String(r)?t.selected=!0:t.selected=!1}return}e.value=String(null!=r?r:"")}function A(e,t){for(const n of e.elements){if(d(n)&&m(n),!f(n)||!n.name)continue;g(n,s(t,y(n)))}}function E(e,t){return Object.keys(e||{}).reduce(((n,r)=>Object.assign(Object.assign({},n),{[r]:t(e[r])})),{})}function w(e){return function(t){if(i(t)){return function(e,t){var n={};for(var r in e)Object.prototype.hasOwnProperty.call(e,r)&&t.indexOf(r)<0&&(n[r]=e[r]);if(null!=e&&"function"==typeof Object.getOwnPropertySymbols){var i=0;for(r=Object.getOwnPropertySymbols(e);i<r.length;i++)t.indexOf(r[i])<0&&Object.prototype.propertyIsEnumerable.call(e,r[i])&&(n[r[i]]=e[r[i]])}return n}(O(t,e),["key"])}return e}}function O(e,t){return E(e,(e=>i(e)?O(e,t):Array.isArray(e)?e.map(w(t)):t))}function S(e=8){const t="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";let n="";for(let r=0;r<e;r++)n+=t.charAt(Math.floor(62*Math.random()));return n}function T(e,t){if(!e||Object(e)!==e)return;void 0!==e&&(e=o(e));const n=Array.isArray(t)?t:t.toString().match(/[^.[\]]+/g)||[],r=1===n.length?e:s(e,n.slice(0,-1).join("."));return Array.isArray(r)?r.splice(Number(n[n.length-1]),1):null==r||delete r[n[n.length-1]],e}function j(...e){const t=e.pop(),n=e.shift();if("string"==typeof n)return n;const r=o(n);if(0===e.length)return r;for(const n of e){if(!n)continue;if("string"==typeof n)return n;let e=t(r,n);if(void 0!==e)return e;const a=Array.from(new Set(Object.keys(r).concat(Object.keys(n))));for(const s of a)if(e=t(r[s],n[s]),void 0!==e)r[s]=e;else if(i(n[s])&&i(r[s]))r[s]=j(r[s],n[s],t);else if(Array.isArray(n[s]))r[s]=n[s].map(((e,n)=>{if(!i(e))return e;return j(Array.isArray(r[s])?r[s][n]:r[s],e,t)}));else if(i(n[s])){const e=O(o(n[s]),void 0);r[s]=j(e,n[s],t)}else void 0!==n[s]&&(r[s]=n[s])}return r}function k(...e){return j(...e,(()=>{}))}function x(e,t){return function(e,t){return Object.keys(e).some((n=>t(e[n])))}(e,(e=>i(e)?x(e,t):Array.isArray(e)?0===e.length||e.every((e=>"string"==typeof e))?t(e):e.some((e=>i(e)?x(e,t):t(e))):t(e)))}function V(e){let t;return function(e,...t){const n=e.subscribe(...t);return n.unsubscribe?()=>n.unsubscribe():n}(e,(e=>t=e))(),t}function N(e,t){var n={};for(var r in e)Object.prototype.hasOwnProperty.call(e,r)&&t.indexOf(r)<0&&(n[r]=e[r]);if(null!=e&&"function"==typeof Object.getOwnPropertySymbols){var i=0;for(r=Object.getOwnPropertySymbols(e);i<r.length;i++)t.indexOf(r[i])<0&&Object.prototype.propertyIsEnumerable.call(e,r[i])&&(n[r[i]]=e[r[i]])}return n}function L(e,t){return E(e,(e=>i(e)?L(e,t):Array.isArray(e)?0===e.length||e.every((e=>"string"==typeof e))?t:e.map((e=>N(L(e,t),["key"]))):t))}function F(e){return e?E(e,(e=>i(e)?F(e):Array.isArray(e)?0===e.length||e.every((e=>"string"==typeof e))?e:e.map((e=>{if(!i(e))return e;const t=F(e);return t.key||(t.key=S()),t})):e)):{}}function D(e){return e?E(e,(e=>i(e)?D(e):Array.isArray(e)?0===e.length||e.every((e=>"string"==typeof e))?e:e.map((e=>{if(!i(e))return e;return N(D(e),["key"])})):e)):{}}n.d(t,{N:()=>te});class P extends Error{constructor(e,t){super(e),this.name="FelteSubmitError",this.response=t}}function _(e,t,n,r){return a(e,t,(e=>void 0===e||Array.isArray(e)?(e||(e=[]),void 0===r?e.push(n):e.splice(r,0,n),e):e))}function I(e){return"function"==typeof e}function C(e){return(t,n)=>{if("string"==typeof t){const r=t;e((e=>{const t=I(n)?n(s(e,r)):n;return u(e,r,t)}))}else e((e=>I(t)?t(e):t))}}function H({stores:e,config:t,validateErrors:n,validateWarnings:r,_getCurrentExtenders:c}){var l;let d,v=F(null!==(l=t.initialValues)&&void 0!==l?l:{});const{data:y,touched:p,errors:m,warnings:h,isDirty:b,isSubmitting:g,interacted:E}=e,w=C(y.update),j=C(p.update),N=C(m.update),I=C(h.update);function H(e){w((t=>{const n=e(t);return d&&A(d,n),n}))}const $=(e,t,n)=>{C(H)(e,t),"string"==typeof e&&n&&j(e,!0)};function M(e,t,n){const r=!!i(t)&&L(t,!1),o=i(r)?O(r,[]):[];t=i(t)?Object.assign(Object.assign({},t),{key:S()}):t,m.update((t=>_(t,e,o,n))),h.update((t=>_(t,e,o,n))),p.update((t=>_(t,e,r,n))),y.update((r=>{const i=_(r,e,t,n);return setTimeout((()=>d&&A(d,i))),i}))}function R(e){m.update(e),h.update(e),p.update(e),y.update((t=>{const n=e(t);return setTimeout((()=>d&&A(d,n))),n}))}function q(e){R((t=>T(t,e)))}function K(e,t,n){R((r=>function(e,t,n,r){return a(e,t,(e=>e&&Array.isArray(e)?([e[n],e[r]]=[e[r],e[n]],e):e))}(r,e,t,n)))}function U(e,t,n){R((r=>function(e,t,n,r){return a(e,t,(e=>e&&Array.isArray(e)?(e.splice(r,0,e.splice(n,1)[0]),e):e))}(r,e,t,n)))}function W(e){const t=s(v,e),n=!!i(t)&&L(t,!1),r=i(n)?O(n,[]):[];y.update((n=>{const r=u(n,e,t);return d&&A(d,r),r})),p.update((t=>u(t,e,n))),m.update((t=>u(t,e,r))),h.update((t=>u(t,e,r)))}const G=C(g.update),B=C(b.update),Z=C(E.update);function J(){$(o(v)),j((e=>O(e,!1))),E.set(null),b.set(!1)}function X(e){return async function(i){var o,a,s,u,l,v,b;const{createErrorEvent:A,createSubmitEvent:S,createSuccessEvent:T}=function(){class e extends CustomEvent{constructor(e){super("feltesuccess",{detail:e})}}class t extends CustomEvent{constructor(e){super("felteerror",{detail:e,cancelable:!0})}setErrors(e){this.preventDefault(),this.errors=e}}class n extends Event{constructor(){super("feltesubmit",{cancelable:!0})}handleSubmit(e){this.onSubmit=e}handleError(e){this.onError=e}handleSuccess(e){this.onSuccess=e}}return{createErrorEvent:e=>new t(e),createSubmitEvent:()=>new n,createSuccessEvent:t=>new e(t)}}(),F=S();null==d||d.dispatchEvent(F);const _=null!==(a=null!==(o=F.onError)&&void 0!==o?o:null==e?void 0:e.onError)&&void 0!==a?a:t.onError,C=null!==(u=null!==(s=F.onSuccess)&&void 0!==s?s:null==e?void 0:e.onSuccess)&&void 0!==u?u:t.onSuccess,H=null!==(b=null!==(v=null!==(l=F.onSubmit)&&void 0!==l?l:null==e?void 0:e.onSubmit)&&void 0!==v?v:t.onSubmit)&&void 0!==b?b:function(e){if(e)return async function(){let t=new FormData(e);const n=new URL(e.action),r="get"===e.method.toLowerCase()?"get":n.searchParams.get("_method")||e.method;let i,o=e.enctype;e.querySelector('input[type="file"]')&&(o="multipart/form-data"),"get"!==r&&"application/x-www-form-urlencoded"!==o||(t=new URLSearchParams(t)),"get"===r?(t.forEach(((e,t)=>{n.searchParams.append(t,e)})),i={method:r,headers:{Accept:"application/json"}}):i={method:r,body:t,headers:Object.assign(Object.assign({},"multipart/form-data"!==o&&{"Content-Type":o}),{Accept:"application/json"})};const a=await window.fetch(n.toString(),i);if(a.ok)return a;throw new P("An error occurred while submitting the form",a)}}(d);if(!H)return;if(null==i||i.preventDefault(),F.defaultPrevented)return;g.set(!0),E.set(null);const R=D(V(y)),G=await n(R,null==e?void 0:e.validate),B=await r(R,null==e?void 0:e.warn);if(B&&h.set(k(O(R,[]),B)),p.set(L(R,!0)),G){p.set(L(G,!0));if(x(G,(e=>Array.isArray(e)?e.length>=1:!!e)))return await new Promise((e=>setTimeout(e))),c().forEach((e=>{var t;return null===(t=e.onSubmitError)||void 0===t?void 0:t.call(e,{data:R,errors:G})})),void g.set(!1)}const Z={event:i,setFields:$,setData:w,setTouched:j,setErrors:N,setWarnings:I,unsetField:q,addField:M,resetField:W,reset:J,setInitialValues:z.setInitialValues,moveField:U,swapFields:K,form:d,controls:d&&Array.from(d.elements).filter(f),config:Object.assign(Object.assign({},t),e)};try{const e=await H(R,Z);null==d||d.dispatchEvent(T(Object.assign({response:e},Z))),await(null==C?void 0:C(e,Z))}catch(e){const t=A(Object.assign({error:e},Z));if(null==d||d.dispatchEvent(t),!_&&!t.defaultPrevented)throw e;if(!_&&!t.errors)return;const n=t.errors||await(null==_?void 0:_(e,Z));n&&(p.set(L(n,!0)),m.set(n),await new Promise((e=>setTimeout(e))),c().forEach((e=>{var t;return null===(t=e.onSubmitError)||void 0===t?void 0:t.call(e,{data:R,errors:V(m)})})))}finally{g.set(!1)}}}const z={setData:w,setFields:$,setTouched:j,setErrors:N,setWarnings:I,setIsSubmitting:G,setIsDirty:B,setInteracted:Z,validate:async function(){const e=V(y);p.set(L(e,!0)),E.set(null);const t=await n(e);return await r(e),t},reset:J,unsetField:q,resetField:W,addField:M,swapFields:K,moveField:U,createSubmitHandler:X,handleSubmit:X(),setInitialValues:e=>{v=F(e)}};return{public:z,private:{_setFormNode(e){d=e},_getInitialValues:()=>v}}}function $(e){let t=e;for(;t&&"FORM"!==t.nodeName;){if(t.hasAttribute("data-felte-ignore"))return!0;t=t.parentElement}return!1}function M(e,t,{onInit:n,onEnd:r}={}){let i;return(...o)=>{i||null==n||n(),i&&clearTimeout(i),i=setTimeout((()=>{e.apply(this,o),i=void 0,null==r||r()}),t)}}function R(e,t){if(!i(e)||!i(t)){if(Array.isArray(t)){if(t.some(i))return;const n=Array.isArray(e)?e:[];return t.map(((e,t)=>{var r;return null!==(r=n[t])&&void 0!==r?r:e}))}return void 0!==e?e:void 0}}function q(...e){return j(...e,R)}function K({helpers:e,stores:t,config:n,extender:r,createSubmitHandler:a,handleSubmit:d,_setFormNode:m,_getInitialValues:g,_setCurrentExtenders:A,_getCurrentExtenders:E}){const{setFields:w,setTouched:O,reset:S,setInitialValues:j}=e,{addValidator:x,addTransformer:N,validate:L}=e,{data:F,errors:D,warnings:P,touched:_,isSubmitting:I,isDirty:C,interacted:H,isValid:R,isValidating:K}=t;return{form:function(t){function U(e){return function(r){return r({form:t,stage:e,controls:Array.from(t.elements).filter(f),data:F,errors:D,warnings:P,touched:_,isValid:R,isValidating:K,isSubmitting:I,isDirty:C,interacted:H,config:n,addValidator:x,addTransformer:N,setFields:w,validate:L,reset:S,createSubmitHandler:a,handleSubmit:d})}}t.requestSubmit||(t.requestSubmit=d),A(r.map(U("MOUNT"))),t.noValidate=!!n.validate;const{defaultData:W,defaultTouched:G}=b(t);function B(e){const t=e.target;if(!t||!f(t)||l(t)||$(t))return;if(["checkbox","radio","file"].includes(t.type))return;if(!t.name)return;C.set(!0);const n=h(t);H.set(t.name),F.update((e=>u(e,y(t),n)))}function Z(e){const n=e.target;if(n&&f(n)&&!$(n)&&n.name)if(O(y(n),!0),H.set(n.name),(l(n)||["checkbox","radio","file","hidden"].includes(n.type))&&C.set(!0),"hidden"===n.type&&F.update((e=>u(e,y(n),n.value))),l(n))!function(e){if(e.multiple){const t=Array.from(e.selectedOptions).map((e=>e.value));F.update((n=>u(n,y(e),t)))}else F.update((t=>u(t,y(e),e.value)))}(n);else{if(!c(n))return;"checkbox"===n.type?function(e){const n=y(e),r=Array.from(t.querySelectorAll(`[name="${e.name}"]`)).filter((e=>!!f(e)&&n===y(e)));if(0!==r.length)1===r.length?F.update((t=>u(t,y(e),e.checked))):F.update((t=>u(t,y(e),r.filter(c).filter((e=>e.checked)).map((e=>e.value)))))}(n):"radio"===n.type?function(e){const n=t.querySelectorAll(`[name="${e.name}"]`),r=Array.from(n).find((e=>c(e)&&e.checked));F.update((t=>u(t,y(e),null==r?void 0:r.value)))}(n):"file"===n.type&&function(e){var t;const n=Array.from(null!==(t=e.files)&&void 0!==t?t:[]);F.update((t=>u(t,y(e),e.multiple?n:n[0])))}(n)}}function J(e){const t=e.target;t&&f(t)&&!$(t)&&t.name&&(O(y(t),!0),H.set(t.name))}function X(e){e.preventDefault(),S()}m(t),j(k(o(W),g())),w(g()),_.set(G);const z=M((()=>{E().forEach((e=>{var t;return null===(t=e.destroy)||void 0===t?void 0:t.call(e)})),A(r.map(U("UPDATE")));const{defaultData:n,defaultTouched:i}=b(t);F.update((e=>q(e,n))),_.update((e=>q(e,i))),e.setFields(V(F))}),0);let Y=[];const Q=M((()=>{E().forEach((e=>{var t;return null===(t=e.destroy)||void 0===t?void 0:t.call(e)})),A(r.map(U("UPDATE"))),function(e){let t=V(F),n=V(_),r=V(D),o=V(P);for(const a of e.reverse()){if(a.hasAttribute("data-felte-keep-on-remove")&&"false"!==a.dataset.felteKeepOnRemove)continue;const e=/.*(\[[0-9]+\]|\.[0-9]+)\.[^.]+$/;let u=y(a);const c=V(_);if(e.test(u)){const e=u.split(".").slice(0,-1).join("."),t=s(c,e);i(t)&&Object.keys(t).length<=1&&(u=e)}t=T(t,u),n=T(n,u),r=T(r,u),o=T(o,u)}F.set(t),_.set(n),D.set(r),P.set(o)}(Y),Y=[]}),0);function ee(e){const t=Array.from(e.addedNodes).some((e=>{if(!v(e))return!1;if(f(e))return!0;return p(e).length>0}));t&&z()}function te(e){for(const t of e.removedNodes){if(!v(t))continue;const e=p(t);0!==e.length&&(Y.push(...e),Q())}}const ne=new MutationObserver((function(e){for(const t of e)"childList"===t.type&&(t.addedNodes.length>0&&ee(t),t.removedNodes.length>0&&te(t))}));ne.observe(t,{childList:!0,subtree:!0}),t.addEventListener("input",B),t.addEventListener("change",Z),t.addEventListener("focusout",J),t.addEventListener("submit",d),t.addEventListener("reset",X);const re=D.subscribe((e=>{for(const n of t.elements){if(!f(n)||!n.name)continue;const t=s(e,y(n)),r=Array.isArray(t)?t.join("\n"):"string"==typeof t?t:void 0;r!==n.dataset.felteValidationMessage&&(r?(n.dataset.felteValidationMessage=r,n.setAttribute("aria-invalid","true")):(delete n.dataset.felteValidationMessage,n.removeAttribute("aria-invalid")))}}));return{destroy(){ne.disconnect(),t.removeEventListener("input",B),t.removeEventListener("change",Z),t.removeEventListener("focusout",J),t.removeEventListener("submit",d),t.removeEventListener("reset",X),re(),E().forEach((e=>{var t;return null===(t=e.destroy)||void 0===t?void 0:t.call(e)}))}}}}}function U(e,t){if(!i(e)&&!i(t)){if(null===e||""===e)return t;if(null===t||""===t)return e;if(!t)return e;if(e&&t){if(Array.isArray(e)){if(!Array.isArray(t))return[...e,t];const n=[],r=Math.max(t.length,e.length);for(let o=0;o<r;o++){let r=e[o],a=t[o];i(r)||i(a)?n.push(W([null!=r?r:{},null!=a?a:{}])):(Array.isArray(r)||(r=[r]),Array.isArray(a)||(a=[a]),n.push(...r,...a))}return n.filter(Boolean)}return Array.isArray(t)||(t=[t]),[e,...t].reduce(((e,t)=>e.concat(t)),[]).filter(Boolean)}}}function W(e){return j(...e,U)}function G(e,t){if(i(e))return!t||i(t)&&0===Object.keys(t).length?O(e,null):void 0;if(Array.isArray(e)){if(e.some(i))return;const n=Array.isArray(t)?t:[];return e.map(((e,t)=>{const r=n[t];return Array.isArray(r)&&0===r.length?null:e&&r||null}))}return Array.isArray(t)&&0===t.length?null:Array.isArray(t)?e?t:null:e&&t?[t]:null}function B(e,t){if(i(e))return!t||i(t)&&0===Object.keys(t).length?O(e,null):void 0;if(Array.isArray(e)){if(e.some(i))return;const n=Array.isArray(t)?t:[];return e.map(((e,t)=>{const r=n[t];return Array.isArray(r)&&0===r.length?null:r||null}))}return Array.isArray(t)&&0===t.length?null:Array.isArray(t)?t:t?[t]:null}function Z([e,t]){return j(t,e,G)}function J([e,t]){return j(t,e,B)}function X(e,t){var n,i,a,s,u,c,l,d,f;const v=function(e){return function(t,n,r){const i=Array.isArray(t)?t:[t],o=new Array(i.length),a=e(r),s=a.set,u=a.subscribe;let c;return a.subscribe=function(e){const t=u(e);return()=>{t()}},[a,function(){c=i.map(((e,t)=>e.subscribe((e=>{o[t]=e,s(n(o))}))))},function(){null==c||c.forEach((e=>e()))}]}}(e),y=t.initialValues=t.initialValues?F(r(o(t.initialValues),t.transform)):{},p=L(D(y),!1),m=e(p),h=e(0),[b,g,A]=v([m,h],(([e,t])=>x(e,(e=>!!e))&&t>=1),!1);function E(e){let t;return async function(n,r,i,o=!1){if(!i||!n)return;let a=r&&Object.keys(r).length>0?r:O(n,[]);const s=function(e){const t={aborted:!1,priority:e};return{signal:t,abort(){t.aborted=!0}}}(o);if((null==t?void 0:t.signal.priority)&&!o||(null==t||t.abort(),t=s),t.signal.priority&&!o)return;h.update((e=>e+1));const u=(c=D(n),(l=i)?(Array.isArray(l)?l:[l]).map((e=>e(c))):[]);var c,l;return u.forEach((async t=>{const n=await t;s.signal.aborted||(a=W([a,n]),e.set(a))})),await Promise.all(u),t=void 0,h.update((e=>e-1)),a}}delete b.set,delete b.update;let w=O(p,[]);const S=e(y),T=O(p,[]),j=e(T),k=e(o(T)),[V,N,P]=v([j,k],W,o(T)),_=O(p,[]),I=e(_),C=e(o(_)),[H,$,R]=v([I,C],W,o(_)),[q,K,U]=v([V,m],Z,o(T)),[G,B,X]=v([H,m],J,o(_));let z=!1;const[Y,Q,ee]=v(V,(([e])=>{var n;return z?!x(e,(e=>Array.isArray(e)?e.length>=1:!!e)):(z=!0,!t.validate&&!(null===(n=t.debounced)||void 0===n?void 0:n.validate))}),!t.validate&&!(null===(n=t.debounced)||void 0===n?void 0:n.validate));delete Y.set,delete Y.update;const te=e(!1),ne=e(!1),re=e(null),ie=E(j),oe=E(I),ae=E(k),se=E(C),ue=M(ae,null!==(u=null!==(a=null===(i=t.debounced)||void 0===i?void 0:i.validateTimeout)&&void 0!==a?a:null===(s=t.debounced)||void 0===s?void 0:s.timeout)&&void 0!==u?u:300,{onInit:()=>{h.update((e=>e+1))},onEnd:()=>{h.update((e=>e-1))}}),ce=M(se,null!==(f=null!==(l=null===(c=t.debounced)||void 0===c?void 0:c.warnTimeout)&&void 0!==l?l:null===(d=t.debounced)||void 0===d?void 0:d.timeout)&&void 0!==f?f:300);let le=T,de=_;function fe(){const e=S.subscribe((e=>{var n,r;const i=D(e);ie(i,w,t.validate),oe(i,w,t.warn),ue(i,w,null===(n=t.debounced)||void 0===n?void 0:n.validate),ce(i,w,null===(r=t.debounced)||void 0===r?void 0:r.warn)})),n=m.subscribe((e=>{w=O(e,[])})),r=V.subscribe((e=>{le=e})),i=H.subscribe((e=>{de=e}));return N(),Q(),$(),K(),B(),g(),function(){e(),U(),P(),R(),X(),ee(),A(),n(),r(),i()}}function ve(e){j.set(e(le)),k.set({})}function ye(e){I.set(e(de)),C.set({})}return q.set=function(e){ve((()=>e))},q.update=ve,G.set=function(e){ye((()=>e))},G.update=ye,{data:S,errors:q,warnings:G,touched:m,isValid:Y,isSubmitting:te,isDirty:ne,isValidating:b,interacted:re,validateErrors:async function(e,n){var r;const i=ie(e,w,null!=n?n:t.validate,!0);if(n)return i;const o=ae(e,w,null===(r=t.debounced)||void 0===r?void 0:r.validate,!0);return W(await Promise.all([i,o]))},validateWarnings:async function(e,n){var r;const i=oe(e,w,null!=n?n:t.warn,!0);if(n)return i;const o=se(e,w,null===(r=t.debounced)||void 0===r?void 0:r.warn,!0);return W(await Promise.all([i,o]))},cleanup:t.preventStoreStart?()=>{}:fe(),start:fe}}var z=n(74985);const Y=[];function Q(e,t=z.ZTd){let n;const r=new Set;function i(t){if((0,z.N8)(e,t)&&(e=t,n)){const t=!Y.length;for(const t of r)t[1](),Y.push(t,e);if(t){for(let e=0;e<Y.length;e+=2)Y[e][0](Y[e+1]);Y.length=0}}}function o(t){i(t(e))}return{set:i,update:o,subscribe:function(a,s=z.ZTd){const u=[a,s];return r.add(u),1===r.size&&(n=t(i,o)||z.ZTd),a(e),()=>{r.delete(u),0===r.size&&n&&(n(),n=null)}}}}var ee=n(74982);function te(e){const t=function(e,t){var n,i;function o(t,{debounced:n,level:r}={debounced:!1,level:"error"}){var i;const o="error"===r?"validate":"warn";null!==(i=e.debounced)&&void 0!==i||(e.debounced={});const a=n?e.debounced:e;a[o]?a[o]=[...a[o],t]:a[o]=[t]}function a(t){e.transform?e.transform=[...e.transform,t]:e.transform=[t]}null!==(n=e.extend)&&void 0!==n||(e.extend=[]),null!==(i=e.debounced)&&void 0!==i||(e.debounced={}),e.validate&&!Array.isArray(e.validate)&&(e.validate=[e.validate]),e.debounced.validate&&!Array.isArray(e.debounced.validate)&&(e.debounced.validate=[e.debounced.validate]),e.transform&&!Array.isArray(e.transform)&&(e.transform=[e.transform]),e.warn&&!Array.isArray(e.warn)&&(e.warn=[e.warn]),e.debounced.warn&&!Array.isArray(e.debounced.warn)&&(e.debounced.warn=[e.debounced.warn]);const s=Array.isArray(e.extend)?e.extend:[e.extend];let u=[];const c=()=>u,{isSubmitting:l,isValidating:d,data:f,errors:v,warnings:y,touched:p,isValid:m,isDirty:h,cleanup:b,start:g,validateErrors:A,validateWarnings:E,interacted:w}=X(t.storeFactory,e),O=f.update,S=f.set;f.update=t=>O((n=>F(r(t(n),e.transform)))),f.set=t=>S(F(r(t,e.transform)));const T=H({extender:s,config:e,addValidator:o,addTransformer:a,validateErrors:A,validateWarnings:E,_getCurrentExtenders:c,stores:{data:f,errors:v,warnings:y,touched:p,isValid:m,isValidating:d,isSubmitting:l,isDirty:h,interacted:w}}),{createSubmitHandler:j,handleSubmit:k}=T.public;u=s.map((t=>t({stage:"SETUP",errors:v,warnings:y,touched:p,data:f,isDirty:h,isValid:m,isValidating:d,isSubmitting:l,interacted:w,config:e,addValidator:o,addTransformer:a,setFields:T.public.setFields,reset:T.public.reset,validate:T.public.validate,handleSubmit:k,createSubmitHandler:j})));const x=Object.assign({config:e,stores:{data:f,touched:p,errors:v,warnings:y,isSubmitting:l,isValidating:d,isValid:m,isDirty:h,interacted:w},createSubmitHandler:j,handleSubmit:k,helpers:Object.assign(Object.assign({},T.public),{addTransformer:a,addValidator:o}),extender:s,_getCurrentExtenders:c,_setCurrentExtenders:e=>{u=e}},T.private),{form:V}=K(x);return Object.assign({data:f,errors:v,warnings:y,touched:p,isValid:m,isSubmitting:l,isValidating:d,isDirty:h,interacted:w,form:V,cleanup:b,startStores:g},T.public)}(null!=e?e:{},{storeFactory:Q}),{cleanup:n,startStores:i}=t,o=function(e,t){var n={};for(var r in e)Object.prototype.hasOwnProperty.call(e,r)&&t.indexOf(r)<0&&(n[r]=e[r]);if(null!=e&&"function"==typeof Object.getOwnPropertySymbols){var i=0;for(r=Object.getOwnPropertySymbols(e);i<r.length;i++)t.indexOf(r[i])<0&&Object.prototype.propertyIsEnumerable.call(e,r[i])&&(n[r[i]]=e[r[i]])}return n}(t,["cleanup","startStores"]);return(0,ee.ev)(n),o}},74982:(e,t,n)=>{n.d(t,{H3:()=>r.H3E,Ky:()=>r.KyG,ev:()=>r.evW,x:()=>r.xa3});var r=n(74985)},89108:(e,t,n)=>{n.d(t,{$T:()=>l,AT:()=>g,Dh:()=>m,Ee:()=>i,FW:()=>V,Fv:()=>o,Hb:()=>N,Kp:()=>S,Lj:()=>A,R3:()=>a,RM:()=>f,Ut:()=>x,VH:()=>k,bG:()=>v,cS:()=>h,fL:()=>p,oL:()=>b,og:()=>d,pI:()=>T,qO:()=>s,rT:()=>j});n(68399);let r=!1;function i(){r=!0}function o(){r=!1}function a(e,t){e.appendChild(t)}function s(e,t,n){const r=u(e);if(!r.getElementById(t)){const e=v("style");e.id=t,e.textContent=n,c(r,e)}}function u(e){if(!e)return document;const t=e.getRootNode?e.getRootNode():e.ownerDocument;return t&&t.host?t:e.ownerDocument}function c(e,t){return a(e.head||e,t),t.sheet}function l(e,t,n){e.insertBefore(t,n||null)}function d(e){e.parentNode&&e.parentNode.removeChild(e)}function f(e,t){for(let n=0;n<e.length;n+=1)e[n]&&e[n].d(t)}function v(e){return document.createElement(e)}function y(e){return document.createElementNS("http://www.w3.org/2000/svg",e)}function p(e){return document.createTextNode(e)}function m(){return p(" ")}function h(){return p("")}function b(e,t,n,r){return e.addEventListener(t,n,r),()=>e.removeEventListener(t,n,r)}function g(e){return function(t){return t.preventDefault(),e.call(this,t)}}function A(e,t,n){null==n?e.removeAttribute(t):e.getAttribute(t)!==n&&e.setAttribute(t,n)}const E=["width","height"];function w(e,t){const n=Object.getOwnPropertyDescriptors(e.__proto__);for(const r in t)null==t[r]?e.removeAttribute(r):"style"===r?e.style.cssText=t[r]:"__value"===r?e.value=e[r]=t[r]:n[r]&&n[r].set&&-1===E.indexOf(r)?e[r]=t[r]:A(e,r,t[r])}function O(e,t){Object.keys(t).forEach((n=>{!function(e,t,n){const r=t.toLowerCase();r in e?e[r]="boolean"==typeof e[r]&&""===n||n:t in e?e[t]="boolean"==typeof e[t]&&""===n||n:A(e,t,n)}(e,n,t[n])}))}function S(e){return/-/.test(e)?O:w}function T(e){return Array.from(e.childNodes)}function j(e,t){t=""+t,e.data!==t&&(e.data=t)}function k(e,t,n){e.classList.toggle(t,!!n)}function x(e,t,{bubbles:n=!1,cancelable:r=!1}={}){return new CustomEvent(e,{detail:t,bubbles:n,cancelable:r})}class V{is_svg=!1;e=void 0;n=void 0;t=void 0;a=void 0;constructor(e=!1){this.is_svg=e,this.e=this.n=null}c(e){this.h(e)}m(e,t,n=null){this.e||(this.is_svg?this.e=y(t.nodeName):this.e=v(11===t.nodeType?"TEMPLATE":t.nodeName),this.t="TEMPLATE"!==t.tagName?t:t.content,this.c(e)),this.i(n)}h(e){this.e.innerHTML=e,this.n=Array.from("TEMPLATE"===this.e.nodeName?this.e.content.childNodes:this.e.childNodes)}i(e){for(let t=0;t<this.n.length;t+=1)l(this.t,this.n[t],e)}p(e){this.d(),this.h(e),this.i(this.a)}d(){this.n.forEach(d)}}function N(e){const t={};return e.childNodes.forEach((e=>{t[e.slot||"default"]=!0})),t}},74985:(e,t,n)=>{n.d(t,{$Tr:()=>r.$T,AT7:()=>r.AT,DhX:()=>r.Dh,FIv:()=>c.FI,FWw:()=>r.FW,H1I:()=>c.Gu,H3E:()=>o.H3,Jn4:()=>c.Jn,Jvk:()=>c.Jv,Kp5:()=>r.Kp,KyG:()=>a.Ky,Ljt:()=>r.Lj,LoY:()=>s.L,N8:()=>c.N8,NXn:()=>i.NX,R3I:()=>r.R3,RMB:()=>r.RM,S1n:()=>l.S1,TVh:()=>c.TV,Ui:()=>u.Ui,VHj:()=>r.VH,VOJ:()=>c.VO,VnY:()=>a.Vn,XGm:()=>c.XG,YCL:()=>l.YC,ZTd:()=>c.ZT,akz:()=>l.ak,bGB:()=>r.bG,cKT:()=>o.cK,cSb:()=>r.cS,dvw:()=>u.dv,etI:()=>u.et,evW:()=>o.ev,f0i:()=>c.f0,fLW:()=>r.fL,f_C:()=>l.f_,gbL:()=>u.gb,hjT:()=>a.hj,j7q:()=>c.j7,kmG:()=>c.km,nuO:()=>c.nu,oLt:()=>r.oL,ogt:()=>r.og,q2N:()=>c.q2,qOq:()=>r.qO,rTO:()=>r.rT,sBU:()=>c.sB,u2N:()=>c.u2,vpE:()=>l.vp,xa3:()=>o.x,yef:()=>l.ye});n(63480),n(5387);var r=n(89108),i=(n(55763),n(31505),n(13111)),o=n(46788),a=(n(50637),n(44098)),s=n(66120),u=(n(30501),n(42938)),c=n(84148),l=n(29864);n(11319)},46788:(e,t,n)=>{n.d(t,{H3:()=>s,cK:()=>l,ev:()=>u,lu:()=>o,x:()=>c,xL:()=>i});var r=n(89108);let i;function o(e){i=e}function a(){if(!i)throw new Error("Function called outside component initialization");return i}function s(e){a().$$.on_mount.push(e)}function u(e){a().$$.on_destroy.push(e)}function c(){const e=a();return(t,n,{cancelable:i=!1}={})=>{const o=e.$$.callbacks[t];if(o){const a=(0,r.Ut)(t,n,{cancelable:i});return o.slice().forEach((t=>{t.call(e,a)})),!a.defaultPrevented}return!0}}function l(e,t){const n=e.$$.callbacks[t.type];n&&n.slice().forEach((e=>e.call(this,t)))}},84148:(e,t,n)=>{function r(){}n.d(t,{FI:()=>y,Gu:()=>O,H1:()=>f,Jn:()=>d,Jv:()=>A,KH:()=>o,N8:()=>c,TV:()=>S,VO:()=>g,XG:()=>w,ZT:()=>r,f0:()=>i,j7:()=>s,km:()=>b,ku:()=>a,nu:()=>p,q2:()=>E,sB:()=>u,u2:()=>h});function i(e,t){for(const n in t)e[n]=t[n];return e}function o(e){return e()}function a(){return Object.create(null)}function s(e){e.forEach(o)}function u(e){return"function"==typeof e}function c(e,t){return e!=e?t==t:e!==t||e&&"object"==typeof e||"function"==typeof e}let l;function d(e,t){return e===t||(l||(l=document.createElement("a")),l.href=t,e===l.href)}function f(e){return 0===Object.keys(e).length}function v(e,...t){if(null==e){for(const e of t)e(void 0);return r}const n=e.subscribe(...t);return n.unsubscribe?()=>n.unsubscribe():n}function y(e,t,n){e.$$.on_destroy.push(v(t,n))}function p(e,t,n,r){if(e){const i=m(e,t,n,r);return e[0](i)}}function m(e,t,n,r){return e[1]&&r?i(n.ctx.slice(),e[1](r(t))):n.ctx}function h(e,t,n,r){if(e[2]&&r){const i=e[2](r(n));if(void 0===t.dirty)return i;if("object"==typeof i){const e=[],n=Math.max(t.dirty.length,i.length);for(let r=0;r<n;r+=1)e[r]=t.dirty[r]|i[r];return e}return t.dirty|i}return t.dirty}function b(e,t,n,r,i,o){if(i){const a=m(t,n,r,o);e.p(a,i)}}function g(e){if(e.ctx.length>32){const t=[],n=e.ctx.length/32;for(let e=0;e<n;e++)t[e]=-1;return t}return-1}function A(e){const t={};for(const n in e)"$"!==n[0]&&(t[n]=e[n]);return t}function E(e,t){const n={};t=new Set(t);for(const r in e)t.has(r)||"$"===r[0]||(n[r]=e[r]);return n}function w(e){const t={};for(const n in e)t[n]=!0;return t}function O(e){return null==e?"":e}function S(e){return e&&u(e.destroy)?e.destroy:r}}}]);