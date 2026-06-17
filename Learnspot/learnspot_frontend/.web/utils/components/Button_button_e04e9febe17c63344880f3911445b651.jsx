
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_e04e9febe17c63344880f3911445b651 = memo(({children}) => {
    const on_click_dacbc72eb14d2cdd82e9ff360e63b64b = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___practice____practice_state.load_words", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["cursor"] : "pointer" }),loading:false,onClick:on_click_dacbc72eb14d2cdd82e9ff360e63b64b,size:"3",variant:"soft"},children)
    )
});
