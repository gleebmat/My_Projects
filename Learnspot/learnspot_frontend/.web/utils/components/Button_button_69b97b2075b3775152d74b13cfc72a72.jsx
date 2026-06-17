
import {Fragment,memo,useCallback,useEffect} from "react"
import {ReflexEvent,applyEventActions,isTrue} from "$/utils/state"
import {Button as RadixThemesButton} from "@radix-ui/themes"
import {addEvents} from "$/utils/context"
import {jsx} from "@emotion/react"






export const Button_button_69b97b2075b3775152d74b13cfc72a72 = memo(({children}) => {
    const on_click_c598e97ec436a3dd75ea3c2da6bd6d40 = useCallback(((_e) => (addEvents([(ReflexEvent("reflex___state____state.learnspot___state___auth____auth_state.learnspot___state___practice____practice_state.start_quiz", ({  }), ({  })))], [_e], ({  })))), [addEvents, ReflexEvent])



    return(
        jsx(RadixThemesButton,{color:"teal",css:({ ["cursor"] : "pointer" }),loading:false,onClick:on_click_c598e97ec436a3dd75ea3c2da6bd6d40,size:"3"},children)
    )
});
