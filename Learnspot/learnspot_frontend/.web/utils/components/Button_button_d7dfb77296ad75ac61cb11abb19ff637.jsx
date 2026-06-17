
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_d7dfb77296ad75ac61cb11abb19ff637 = memo(({children}) => {
    const on_click_6fae8b8577575bb69eabc0319fef7393 = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___translation____translation_state.translate", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["cursor"] : "pointer" }),disabled:false,onClick:on_click_6fae8b8577575bb69eabc0319fef7393,size:"3"},children)
    )
});
