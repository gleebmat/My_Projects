
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_0d6febcad99fe3c3fe0da034ee945fe8 = memo(({children}) => {
    const on_click_511ff205984bad547f833320502a3814 = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___texts____text_state.improve_text", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["width"] : "100%", ["cursor"] : "pointer" }),disabled:false,onClick:on_click_511ff205984bad547f833320502a3814,size:"3"},children)
    )
});
