
import {Fragment,memo,useContext,useEffect} from "react"
import {isTrue} from "$/utils/state"
import ReactMarkdown from "react-markdown"
import remarkMath from "remark-math"
import remarkGfm from "remark-gfm"
import rehypeKatex from "rehype-katex"
import "katex/dist/katex.min.css"
import rehypeRaw from "rehype-raw"
import rehypeUnwrapImages from "rehype-unwrap-images"
import {Code as RadixThemesCode,Heading as RadixThemesHeading,Link as RadixThemesLink,Text as RadixThemesText} from "@radix-ui/themes"
import {Link as ReactRouterLink} from "react-router"
import {PrismAsyncLight as SyntaxHighlighter} from "react-syntax-highlighter"
import {ColorModeContext,StateContexts} from "$/utils/context"
import oneLight from "react-syntax-highlighter/dist/esm/styles/prism/one-light"
import oneDark from "react-syntax-highlighter/dist/esm/styles/prism/one-dark"
import {jsx} from "@emotion/react"




        function ComponentMap_d8b2dcef1196f2645c614da09ad39de0 () {
            const { resolvedColorMode } = useContext(ColorModeContext)



            return (
                ({ ["h1"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h1",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"6",...props},children))), ["h2"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h2",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"5",...props},children))), ["h3"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h3",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"4",...props},children))), ["h4"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h4",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"3",...props},children))), ["h5"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h5",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"2",...props},children))), ["h6"] : (({node, children, ...props}) => (jsx(RadixThemesHeading,{as:"h6",css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),size:"1",...props},children))), ["p"] : (({node, children, ...props}) => (jsx(RadixThemesText,{as:"p",css:({ ["marginTop"] : "1em", ["marginBottom"] : "1em" }),...props},children))), ["ul"] : (({node, children, ...props}) => (jsx("ul",{css:({ ["listStyleType"] : "disc", ["marginTop"] : "1em", ["marginBottom"] : "1em", ["marginLeft"] : "1.5rem", ["direction"] : "column" }),...props},children))), ["ol"] : (({node, children, ...props}) => (jsx("ol",{css:({ ["listStyleType"] : "decimal", ["marginTop"] : "1em", ["marginBottom"] : "1em", ["marginLeft"] : "1.5rem", ["direction"] : "column" }),...props},children))), ["li"] : (({node, children, ...props}) => (jsx("li",{css:({ ["marginTop"] : "0.5em", ["marginBottom"] : "0.5em" }),...props},children))), ["a"] : (({node, children, ...props}) => (jsx(RadixThemesLink,{css:({ ["&:hover"] : ({ ["color"] : "var(--accent-8)" }) }),href:"#",...props},children))), ["code"] : (({node, children, ...props}) => (jsx(RadixThemesCode,{...props},children))), ["pre"] : (({node, ...rest}) => { const {node: childNode, className, children: components, ...props} = rest.children.props; const children = String(Array.isArray(components) ? components.join('\n') : components).replace(/\n$/, ''); const match = (className || '').match(/language-(?<lang>.*)/); let _language = match ? match[1] : ''; ;             return jsx(SyntaxHighlighter,{children:children,css:({ ["marginTop"] : "1em", ["marginBottom"] : "1em" }),language:_language,style:((resolvedColorMode?.valueOf?.() === "light"?.valueOf?.()) ? oneLight : oneDark),wrapLongLines:true,...props},);         }) })
            )
        }
        


export const Markdown_reactmarkdown_ca3341cbc49a780659cd2aac7d15543c = memo(({children}) => {
    const reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state = useContext(StateContexts.reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state)



    return(
        jsx(ReactMarkdown,{components:ComponentMap_d8b2dcef1196f2645c614da09ad39de0(),rehypePlugins:[rehypeKatex, rehypeRaw, rehypeUnwrapImages],remarkPlugins:[remarkMath, remarkGfm]},reflex___state____state__learnspot___state___auth____auth_state__learnspot___state___texts____text_state.improved_text_rx_state_)
    )
});
